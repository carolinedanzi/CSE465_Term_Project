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
		std::map<std::string, Data> varTable;
		int lineNum;
		
		std::string trim(std::string* str);
		
		// Gets the first token in the string
		// Find a way to modify line so it removes the first token
		std::string nextToken(std::string* str);
		
		Type determineType(std::string token);
		
		std::string stripQuotes(std::string token);
		
		void raiseError();
	
	public:
		// Constructor
		zpm();
		
		// Destructor
		~zpm();
		
		void parseFile(char* fileName);
		
		// Takes in a line of the source code, parses it,
		// and sends it to the proper function
		void parseStmt(std::string* line);
		
		// 
		void analyzeAssignment(std::string* line);
		
		void analyzePrint(std::string* line);
		
};