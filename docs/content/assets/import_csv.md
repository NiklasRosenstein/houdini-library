+++
title = "Import CSV"
+++

&ndash; Import CSV-like data into Houdini from one or multiple files into
Point or Polygon attributes.

__Features__

* Import one file, or multiple files from a directory
* Supports `.gz` compressed files
* Supports for various dialects (3 common delimiters and quote characters)
* Import the data into geometry as points or primitives
* Filter rows to be imported with a Python expression
* Import as many columns as you need
* Supports conversion to string, integer and float

__Filter__

The "Filter" parameter must be a Python expression that is valid in a Python
`lambda` context. The filter has one variable available, *row*, which is the
raw CSV row (as a list of strings) read from the file(s). The expression must
result in `True` to use the row, or `False` to skip it.

*Note that the "Skip Whitespace" parameter is __not__ applied to the `row`
parameter when the filter is called.*

__Screenshot__

<p align="center"><img src="https://i.imgur.com/SJGiTk4.png"/></p>
<p align="center"><img src="https://i.imgur.com/3Nu0huN.png"/></p>

__Changelog__

*Nothing to see here.*
