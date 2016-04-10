"""
Caroline Danzi
Dr. Zmuda
CSE 465

Note: I used http://www.tutorialspoint.com/python/python_command_line_arguments.htm
to learn how to get command line arguments in Python.  I also used the Python 3
documentation for string methods, and notes from another class for regex syntax.
"""

import sys
import re

# The first command line argument at 0 is the file name, the second will be
# the tsv, and the third will be the tmp file.  
tsvFileName = sys.argv[1]
tmpFileName = sys.argv[2]

# open the tab-separated file for reading
tsvFile = open(tsvFileName, 'r')

# The first line in the tsv file has the column headings
colHeadings = tsvFile.readline().strip().split('\t')

# Build a dictionary of the column headings where the key
# is the string heading and the value is the index
columns = {}
i = 0
for column in colHeadings:
    columns[column] = i
    i += 1

# Get the index of the ID column for file name
idIndex = columns['ID']

for row in tsvFile:
    cells = row.strip().split('\t')
    fileName = cells[idIndex] + '.txt'
    file = open(fileName, 'w')
    tmpFile = open(tmpFileName, 'r')

    # Go through each line in the template file, see if it has
    # any <<tags>>, replace them, and write the string to the output file
    for line in tmpFile:
        # Had help from Kyle B. with finditer
        pattern = re.compile('<<(\w*)>>')
        # finditer returns a sequence of match objects
        matchIterator = pattern.finditer(line)

        # for each match that it finds (there may be multiple in the line)
        # find the appropriate attribute at the index of the column header
        for match in matchIterator:
            header = match.group(1)
            attribute = cells[columns[header]]
            line = re.sub('<<' + header + '>>', attribute, line)
            
        file.write(line)
    file.close()

tsvFile.close()
tmpFile.close()  
        
    
