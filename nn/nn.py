"""
Caroline Danzi
Dr. Zmuda
CSE 465
Nearest Neighbor Problem
"""

import sys
import re
import math

class DataError(Exception):
    def __init__(self, msg):
        self.msg = msg
    def __str__(self):
        return msg

# Input: The file containing the prototype descriptions
# Output: A 2D array of the prototypes - each prototype
# is represented as an array of its data with the element
# at the last index containing the category
def process_prototypes(proto_file):
    # Loop through each line in prototype file
    prototype_file = open(proto_file, 'r')
    prototypes = []
    
    for line in prototype_file:
        line = re.sub('\s*', '', line)
        proto = line.split(',')
        prototypes.append(proto)

    return prototypes

# Takes in the list of prototypes and the file containing
# the unknowns and prints out the category for each
# unknown based on the prototype it is closest to
def find_nearest_neighbor(prototypes, unknown_file):
    unknowns = open(unknown_file, 'r')
    for line in unknowns:
        line = re.sub('\s*', '', line)
        unknown = line.split(',')
        category = categorize(unknown, prototypes)
        print(category)

# Input: An unknown (as a string list), the list of prototypes
# Output: The category of the prototype to which the unknown
# is closest
def categorize(unknown, prototypes):
    min_dist = sys.maxsize
    category = None
    for prototype in prototypes:
        dist = compute_dist(prototype, unknown)
        if dist < min_dist:
            min_dist = dist
            category = prototype[-1]
    return category

# Compute Euclidean distance between prototype and unknown
# sqrt((p1-u1)^2 + (p2-u2)^2 + ... + (pn-un)^2)
def compute_dist(prototype, unknown):
    if len(prototype) != len(unknown) + 1:
        raise DataError('The number of data points in the prototype did not match the number of data points in the unknown')
    sumOfSquares = 0
    # Note: we must loop through the length of the unknown
    # array because the prototype array is one longer because
    # it also holds the category
    for i in range(len(unknown)):
        sumOfSquares += (float(prototype[i]) - float(unknown[i]))**2
    return math.sqrt(sumOfSquares)

if __name__ == "__main__":
    prototype_file = sys.argv[1]
    unknown_file = sys.argv[2]

    prototypes = process_prototypes(prototype_file)
    find_nearest_neighbor(prototypes, unknown_file)
