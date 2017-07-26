+++
title = "NR Import CSV"
+++

<img align="right" src="https://img.shields.io/badge/Houdini-Indie-orange.svg">

&ndash; Import CSV like a boss.

## Features

* Import a single or multiple files at once
* Import from `.gz` compressed files
* Supports for various dialects (common 4 delimiters and 3 quote characters)
* Import into points or primitives
* Filter rows with a Python expression
* Faster than Houdini's "Table Import" node by orders of magnitude

## Filter

The "Filter" parameter must be a Python expression that is valid in a Python
`lambda` context. The filter has one variable available, *row*, which is the
raw CSV row (as a list of strings) read from the file(s). The expression must
result in `True` to use the row, or `False` to skip it.

Example: `row[2].strip() == 'LSB'` will skip all rows where the third column
does not match the string "LSB".

> *Note that the "Skip Whitespace" parameter is __not__ applied to the `row`
> parameter when the filter is called.*

## Screenshot

<p align="center"><img src="https://i.imgur.com/SJGiTk4.png"/></p>
<p align="center"><img src="https://i.imgur.com/3Nu0huN.png"/></p>

## Changelog

* v4
  * fix NameError when loading from a file (bug introduced in v3)
* v3
  * add ability to reference sections from another HDA using the following
    syntax in the File/Directory parameter: `op:path/to/node?filename`
* v2
  * add "Space" delimiter type
* v1
  * initial version

## Icon Attribution

csv_text.png &ndash; Bdate Kaspar/Franziska Sponsel (Creative Commons Attribution) http://findicons.com/icon/84601/csv_text
