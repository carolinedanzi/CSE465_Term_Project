// Caroline Danzi
// Dr. Zmuda
// CSE 465
// This program interprets a simple language that contains assignment statements,
// print statements, and for loops.  Print statments are of the form PRINT A ; where
// A is the thing to print (variable, int, or String).  Assignment statements have the 
// form A = B ; A += B ; A -= B ; A *= B ; where only = and += work for Strings.

#include "zpm.h"
#include <fstream>

zpm::zpm()
{
	
}

zpm::~zpm()
{
	
}

// Help from:
// http://stackoverflow.com/questions/7868936/read-file-line-by-line
void zpm::parseFile(char* fileName)
{
	// Open file for reading
	std::ifstream sourceFile;
	sourceFile.open(fileName);
	
	// Loop through the lines in the file and parse each statement
	std::string line = "";
	while(getline(sourceFile, line))
	{
		lineNum++;
		std::cout << lineNum << " " ;
		parseStmt(&line);
	}
}

void zpm::analyzeAssignment(std::string* line)
{
	std::cout << "Assignment: " << *line << std::endl;
}

// Print the value of a variable, prefixed with the name of the variable and "="
void zpm::analyzePrint(std::string* line)
{
	std::cout << "Print: " << *line << std::endl;
	// Find the middle segment, which is what we need to print
	int firstSpace = line->find_first_of(" ");
	int lastSpace = line->find_last_of(" ");
	
	// Strip off leading and trailing whitespace
	std::string varName = line->substr(firstSpace, (lastSpace - firstSpace));
	
	// Get value of this variable from var table, and throw error if it has not
	// been assigned a value
	//if(varTable.find(varName) == varTable.end())
	//{
		//raiseError();
	//}
	
	std::cout << varName << "=" << std::endl;
}

// Determines which function to send the line to for interpretation
void zpm::parseStmt(std::string* line)
{
	// If print is not in the string, it must be an assignment statement
	if(line->find("PRINT") == -1)
	{
		analyzeAssignment(line);
	} else {
		analyzePrint(line);
	}
}

void zpm::raiseError()
{
	std::cerr << "RUNTIME ERROR: line " << lineNum << std::endl;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr << "Expected one command line argument" << std::endl;
	}
	
	// The first command line argument is the name of the file,
	// the second is the source code file of the program we are interpreting
	char* sourceFileName = argv[1];
	
	zpm* interpreter = new zpm();
	interpreter->parseFile(sourceFileName);
	
	return 0;
}