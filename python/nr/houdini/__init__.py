# The MIT License (MIT)
#
# Copyright (c) 2018 Niklas Rosenstein
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

__author__ = 'Niklas Rosenstein <rosensteinniklas@gmail.com>'
__version__ = '1.0.0'

import functools
import hou
import localimport as _localimport
import os
import weakref

_importer = None
_path = None

def localimport(*args, **kwargs):
  """
  Get or create a new #localimport<_localimport> object for the current
  Houdini file. You should keep a reference to the returned object as
  otherwise it will be lost.

  The returned localimport object will contain as Python module search path
  the python/ directory in the parent directory of the HIP file.

  # Parameters
  args: Forwarded to the localimport constructor.
  kwargs: Forwarded to the localimport constructor.
  develop (bool): Set to #True to create a new, separate localimport object.
    Useful during development when you want to always reload modules from
    the local python/ modules directory.
  """

  global _importer, _path

  develop = kwargs.pop('develop', False)
  python_dir = os.path.join(os.path.dirname(hou.hipFile.path()), 'python')
  if not _importer or python_dir != _path or develop:
    importer = _localimport.localimport([python_dir], *args, **kwargs)
    if not develop:
      _importer = weakref.ref(importer)
      _path = python_dir
  else:
    importer = _importer

  return importer


class operation(object):
  """
  A simpler interface to the #hou.InterruptableOperation context manager.
  """

  def __init__(self, name, long_name=None, open_dialog=False):
    self._op = hou.InterruptableOperation(name, long_name, open_dialog)

  def __enter__(self):
    self._op.__enter__()
    return self

  def __exit__(self, *a):
    return self._op.__exit__(*a)

  def update(self, percentage=-1.0):
    return self._op.updateProgress(percentage)

  def update_long(self, percentage=-1.0, status=None):
    return self._op.updateLongProgress(percentage, status)

  def wraps(self, fun):
    @functools.wraps(fun)
    def wrapper(*a, **kw):
      with self:
        return fun(*a, **kw)
    return wrapper

  @classmethod
  def takes(cls, *args, **kwargs):
    op = cls(*args, **kwargs)
    def decorator(fun):
      @functools.wraps(fun)
      def wrapper(*a, **kw):
        with op:
          return fun(op, *a, **kw)
      return wrapper
    return decorator
