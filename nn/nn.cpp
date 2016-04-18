// Caroline Danzi
// Dr. Zmuda
// CSE 465
// Nearest Neighbor Problem

#include <iostream>
#include <fstream>
#include <stdlib.h>

// Input: the file name of the prototype file
// Output: A 2D array of the prototypes
// Help reading lines from files from: 
// http://stackoverflow.com/questions/7868936/read-file-line-by-line
void parsePrototypes(char* fileName)
{
	std::ifstream prototypeFile;
	prototypeFile.open(fileName);
	std::string line = "";
	while(!prototypeFile.eof())
	{
		getline(prototypeFile, line);
		std::cout << line << std::endl;
	}
	/*
	std::ifstream prototypeFile(fileName);
	std::string line;
	while(std::getline(prototypeFile, line))
	{
		
	}
	std::string* prototypes[] = null;
	return prototypes;
	*/
}

// Input: the list of prototypes and the name of the unknown file
// Returns: nothing
// Prints the category for each unknown data set
void findNearestNeighbor(std::string* prototypes[], std::string fileName)
{
	
}

// Input: 2D array of prototypes, 1D array of unknown data
// Output: double representing category for this unknown
// The category is determined by the closest prototype to the unknown
double categorize(std::string* prototypes[], std::string* unknowns[])
{
	return 0.0;
}

// Input: 1D array of prototype data and 1D array of unknown data
// Output: double representing Euclidean distance between the prototype and 
// the unknown: sqrt((p1-u1)^2 + (p2-u2)^2 + ... + (pn-un)^2)
double computeDistance(std::string* prototypes[], std::string* unknowns[])
{
	return 0.0;
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
	
	std::cout << prototype_file << ", " << unknown_file << std::endl;
	parsePrototypes(prototype_file);
	return 0;
}