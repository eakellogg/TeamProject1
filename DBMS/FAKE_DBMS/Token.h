#pragma once
#include <iostream>

namespace FAKE_DBMS {

	class Token{
	public:
		enum tokenType { VARIABLE, LITERAL, KEYWORD, SYMBOL, OPENPAREN, CLOSEPAREN, COMMA };
		tokenType type; //the type of he token
		std::string content; //what the token contains. ex: "JOIN"

		//constructor
		Token(tokenType t){
			type = t;
		}
	};

};