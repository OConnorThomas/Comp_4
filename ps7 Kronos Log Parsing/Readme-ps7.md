# PS7: Kronos Log Parsing

## Contact
Name:       Thomas O'Connor
Section:    202
Time to Complete:   5 hours


## Description
The project parses a Kronos log file and displays the
appropriate boot information (start lines, end lines,
and time to completion)

### Features
Implimented a LogParser class which contains one method (generateRPT)
which parses the provided log file and writes to an output file of
(filepath.rpt). This file contains the line and time of boot start,
as well as the line and time of boot completion and elapsed time,
or the indication of an incomplete boot.
This is performed across multiple attempted boot cycles.

### Approach
Using the BOOTONLY.rpt as a refrence, I implimented a class which emulates
the provided report. I counted the line numbers using an unsigned int, and checked
for start and end times, included nested starts and EOF ends. Based on the layout of
the given log file, my class logs every start to a boot sequence, prematurely ending
an existing boot sequence where appropriate. My class also logs premature ends including
EOF ends, noting incomplete boots in these scenarios, and complete boots with boot times
in regular scenarios.

### Regex
Used two regexes: one for the beginning of the boot sequence and one for the conclusion.
    rgx1("\\(log\\.c\\.166\\) server started"),
    rgx2("oejs\\.AbstractConnector:Started SelectChannelConnector@0\\.0\\.0\\.0:9080");
The keywords used are backslashes for parentheses and periods.

### Issues
For all given logs, the provided implementation works. If another log file contains a
different syntax for the date and time, the current methods would be insufficient.

### Extra Credit
N/A

## Acknowledgements
N/A
