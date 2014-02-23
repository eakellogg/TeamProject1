

#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <iostream>
#include <vector>
#include "Token.h"

//namespace FAKE_DBMS {

	//the lexer takes input and tokenizes, storing the input as well as an enumerated type to help the parser distinguish different kinds of input


	//take an input file and lex it
	std::vector<std::vector<FAKE_DBMS::Token> > lexFile(std::string fileName);

	//lex a single command or query
	std::vector<FAKE_DBMS::Token> lexInputLine(std::string inputLine);

//};