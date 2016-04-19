// Caroline Danzi
// Dr. Zmuda
// CSE 465
// This program interprets a simple language that contains assignment statements,
// print statements, and for loops.  Print statments are of the form PRINT A ; where
// A is the thing to print (variable, int, or String).  Assignment statements have the 
// form A = B ; A += B ; A -= B ; A *= B ; where only = and += work for Strings.

#include "zpm.h"
#include <fstream>
#include <cstring>

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

// <assignment> 	-> <var_name> <assign_op> <value> ;
// <assign_op>	-> = | += | *= | -=
// <value>			-> string | int
// Convert string to char* help from:
// http://stackoverflow.com/questions/7352099/stdstring-to-char
// http://www.cplusplus.com/reference/string/string/c_str/
void zpm::analyzeAssignment(std::string* line)
{
	std::cout << "Assignment: " << *line << std::endl;
	
	// Get the variable name
	std::string varName = nextToken(line);
	std::cout << "First token: " << varName << std::endl;
	
	// Get the assignment operator (the second token)	
	std::string assignOp = nextToken(line);
	std::cout << "Second token: " << assignOp << std::endl;
	
	// Get the value of the variable
	std::string varValue = nextToken(line);
	// Determine the type of the data value - either a string, int, or variable
	Type varType = determineType(varValue);
	char* str = new char[line->length() + 1];
	std::strcpy(str, line->c_str());
	std::cout << "Copy of line: " << str << std::endl;
	delete str;
	std::cout << "Third token: " << varValue << std::endl;
	
	// Assign based on the type of assignment
	// Throw appropriate error if variable value is used before declaration
	// or if the assignment operator is not appropriate for the type
	
}

// Help on isdigit from 
// http://www.cplusplus.com/reference/cctype/isdigit/
Type zpm::determineType(std::string token)
{
	if(token[0] == '\"') { return typeString; }
	else if(isdigit(token[0])) { return typeInt; }
	else { return typeVar; }
}

// Gets the first token in the string
// Find a way to modify line so it removes the first token
std::string zpm::nextToken(std::string* line)
{
	// Find the first space, which delineates the first token
	int delimiterIndex = line->find_first_of(" ");
	std::string token = line->substr(0, delimiterIndex);
	token = trim(&token);
	
	// Change line to remove the first token
	*line = line->substr(delimiterIndex, (line->length() - delimiterIndex));
	*line = trim(line);
	
	return token;
}

// Print the value of a variable, prefixed with the name of the variable and "="
void zpm::analyzePrint(std::string* line)
{
	// Find the middle segment, which is what we need to print
	int firstSpace = line->find_first_of(" ");
	int lastSpace = line->find_last_of(" ");
	
	// Strip off leading and trailing whitespace
	std::string varName = line->substr(firstSpace, (lastSpace - firstSpace));
	varName = trim(&varName);
	
	// Get value of this variable from var table, and throw error if it has not
	// been assigned a value
	if(varTable.find(varName) == varTable.end())
	{
		raiseError();
	} else {
		// Print out variable value with prefixed
		Data value = varTable[varName];
		std::cout << varName << "=" << std::endl;
	}
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

// Trims leading and trailing whitespace from a string - Help from:
// http://stackoverflow.com/questions/25829143/c-trim-whitespace-from-a-string
std::string zpm::trim(std::string* str)
{
	int begin = str->find_first_not_of(" ");
	int end = str->find_last_not_of(" ");
	return str->substr(begin, (end-begin+1));
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