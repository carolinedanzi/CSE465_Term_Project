// Caroline Danzi
// Dr. Zmuda
// CSE 465
// Nearest Neighbor Problem
// Help with vectors: http://www.cplusplus.com/reference/vector/vector/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h> // for pow, sqrt
#include <limits.h> // For INT_MAX

// Convert a string line with comma-separated values
// to a double array of those values
// stod: http://www.cplusplus.com/reference/string/stod/
std::vector<double> convertStrToDoubleVector(std::string line)
{
	std::vector<double> dataVector;
	int commaIndex = line.find_first_of(',');
	double datum;
	
	// Loop through as long as the line has 
	while(commaIndex != -1)
	{
		// The substring is the first number we need
		// Convert to double and push_back on vector
		datum = std::stod(line.substr(0, commaIndex));
		dataVector.push_back(datum);
		// Chop off the first part of string up to the comma
		line = line.substr(commaIndex + 1, line.length() - (commaIndex + 1));
		// Find the index of first comma, this is also the length of the substring
		commaIndex = line.find_first_of(',');
	}
	// Loop did not include the last number
	datum = std::stod(line);
	dataVector.push_back(datum);
	return dataVector;
}

// Input: the file name of the prototype file
// Output: A 2D array of the prototypes
// Help reading lines from files from: 
// http://stackoverflow.com/questions/7868936/read-file-line-by-line
// http://www.cplusplus.com/forum/windows/48212/
std::vector<std::vector<double>> parsePrototypes(char* fileName)
{
	// Open file for reading
	std::ifstream prototypeFile;
	prototypeFile.open(fileName);
	
	// This will be a vector of arrays
	std::vector<std::vector<double>> prototypes;
	
	// Loop through each line in the file, split it by ',' and add it to 
	// the vector of prototypes
	std::string line = "";
	while(getline(prototypeFile, line))
	{
		prototypes.push_back(convertStrToDoubleVector(line));
	}
	prototypeFile.close();
	return prototypes;
}

// Input: 1D array of prototype data and 1D array of unknown data
// Output: double representing Euclidean distance between the prototype and 
// the unknown: sqrt((p1-u1)^2 + (p2-u2)^2 + ... + (pn-un)^2)
double computeDistance(std::vector<double> prototype, std::vector<double> unknown)
{
	double sum = 0;
	for(int i = 0; i < unknown.size(); i++)
	{
		sum += pow((prototype[i] - unknown[i]), 2);
	}
	return sqrt(sum);
}

// Input: 2D array of prototypes, 1D array of unknown data
// Output: double representing category for this unknown
// The category is determined by the closest prototype to the unknown
double categorize(std::vector<std::vector<double>> prototypes, std::vector<double> unknown)
{
	double minDist = INT_MAX;
	double category;
	for(int i = 0; i < prototypes.size(); i++)
	{
		std::vector<double> prototype = prototypes[i];
		double dist = computeDistance(prototype, unknown);
		if(dist < minDist)
		{
			minDist = dist;
			category = prototype[prototype.size() - 1];
		}
	}
	return category;
}

// Input: the list of prototypes and the name of the unknown file
// Returns: nothing
// Prints the category for each unknown data set
void findNearestNeighbor(std::vector<std::vector<double>> prototypes, char* fileName)
{
	// Open file for reading
	std::ifstream unknownFile;
	unknownFile.open(fileName);
	std::string line = "";
	
	std::vector<double> unknown;
	double category;
	
	while(getline(unknownFile, line))
	{
		unknown = convertStrToDoubleVector(line);
		category = categorize(prototypes, unknown);
		std::cout << category << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cerr << "Expected two command line arguments" << std::endl;
	}
	// The first command line argument is the name of the file,
	// the second is the prototype file and the third is the unknown file 
	char* prototype_file = argv[1];
	char* unknown_file = argv[2];
	
	std::vector<std::vector<double>> prototypes = parsePrototypes(prototype_file);
	findNearestNeighbor(prototypes, unknown_file);
	return 0;
}