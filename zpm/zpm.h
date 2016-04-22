// Caroline Danzi
// Dr. Zmuda
// CSE 465
// Z+- Problem

#include <map>
#include <iostream>
#include <stdlib.h>

// In this language, something can be a string, int, or variable
enum Type {typeString, typeInt, typeVar};

// Discriminated union to store the data value of the variable
// There is a flag to tell whether the type is a string or int
// Help on discriminated unions from:
// http://www.drdobbs.com/cpp/discriminated-unions-i/184403821?pgno=2
// http://stackoverflow.com/questions/4788965/when-would-anyone-use-a-union-is-it-a-remnant-from-the-c-only-days
struct Data
{
	Type typeFlag;
	union
	{
		char* s;
		int i;
	};
};

class zpm
{
	private:
		// Keep track of variables and line numbers
		std::map<std::string, Data> varTable;
		int lineNum;
		
		// Trim leading and trailing whitespace
		std::string trim(std::string* str);
		
		// Gives the next token in a line and removes it from string
		std::string nextToken(std::string* str);
		
		// Determines the enum Type of a particular token
		Type determineType(std::string token);
		
		// Strips the quotations marks from around a token
		std::string stripQuotes(std::string token);
		
		// Prints a runtime error message, deletes char* in var table,
		// and exits program
		void raiseError();
		
		// Deletes the char* pointers in varTable
		void deletePointers();
	
	public:
		// Constructor
		zpm();
		
		// Destructor
		~zpm();
		
		// Gets each line of the file and parses it
		void parseFile(char* fileName);
		
		// Decides whether the statement is an assignment or print statement
		void parseStmt(std::string* line);
		
		// Interprets an assignment statement
		void analyzeAssignment(std::string* line);
		
		// Interprets a print statement
		void analyzePrint(std::string* line);
		
};