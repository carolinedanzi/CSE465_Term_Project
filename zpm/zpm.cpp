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
	
	// Get the assignment operator (the second token)	
	std::string assignOp = nextToken(line);
	
	// Get the value of the right hand side (RHS) of the assignment statement
	std::string stringVal = nextToken(line);
	Data value;
	
	// Determine the type of the RHS - either a string, int, or variable
	Type varType = determineType(stringVal);
	
	switch(varType)
	{
		// If the type of the RHS is a variable, we need to get its value
		// If it does not have a value, it has not been declared so throw an error
		case typeVar:
		{
			if(varTable.find(stringVal) == varTable.end())
			{
				raiseError();
			} else {
				value = varTable[stringVal];
			}
			break;
		}
		// If value is a string, strip the quotes and convert it to a char array
		case typeString:
		{
			value.typeFlag = typeString;
			// Data discriminated union stores char*, not std::string
			stringVal = stripQuotes(stringVal);
			char* str = new char[stringVal.length() + 1];
			std::strcpy(str, stringVal.c_str());
			value.s = str;
			delete str;
			break;
		}
		// If the type is an int, just update the discriminated union
		case typeInt:
		{
			value.typeFlag = typeInt;
			value.i = std::stoi(stringVal);
			break;
		}
		default:
			raiseError();
	}
	
	// Assign based on the type of assignment
	// Throw appropriate error if variable value is used before declaration
	// or if the assignment operator is not appropriate for the type
	if(assignOp == "=")
	{
		varTable[varName] = value;
	}
	
}

// Interprets the type (either variable, string, or int)
// of a string token from the source code
// Help on isdigit from 
// http://www.cplusplus.com/reference/cctype/isdigit/
Type zpm::determineType(std::string token)
{
	if(token[0] == '\"') { return typeString; }
	else if(isdigit(token[0])) { return typeInt; }
	else { return typeVar; }
}

// Strips the quotes off a token - ex: "hello" -> hello
// Input: The string token
// Output: The string token with first and last chars removed
std::string zpm::stripQuotes(std::string token)
{
	return token.substr(1, token.length() - 2);
}

// Gets the first token in the string and removes it
// from the line
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
		switch(value.typeFlag)
		{
			case typeString:
				std::cout << varName << "=" << value.s << std::endl;
				break;
			
			case typeInt:
				std::cout << varName << "=" << value.i << std::endl;
				break;
			
			default:
				std::cout << "Something went wrong in print" << std::endl;
		}
		
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

// Prints out an error message with the line number that 
// contains the error
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
	
	delete interpreter;
	
	return 0;
}