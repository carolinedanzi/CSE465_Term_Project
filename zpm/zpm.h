// Caroline Danzi
// Dr. Zmuda
// CSE 465
// Z+- Problem

#include <map>
#include <iostream>
#include <stdlib.h>

class zpm
{
	private:
		std::map<std::string, std::string> varTable;
		int lineNum;
		
		std::string trim(std::string* str);
		
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