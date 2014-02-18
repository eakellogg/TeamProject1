#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <iostream>
#include <deque>
using namespace std;
const static string FILLER = "FILLER";


class Token {
public:
	// return value of the token
	string getValue(){
		return value;
	}
	
	// trtuen type of the token
	string getType(){
		return type;
	}
	
	// constructor for Token
	Token( string type, string value) : value(value), type(type){}
	
private:
	string value;
	string type;

};

class TokenStream {
public:
	// get a token from the (back of the) token stream
	Token getToken(){
		if (tokens.size() != 0){
			Token t = tokens.back(); 
			tokens.pop_back();  
			return t;
		}
		else return Token(FILLER, "NOTHING HERE");
	}
	
	// push a token back into the (back of the) token stream 
	// used by the parser to replace a token it had already moved
	void pushToken(Token t){ tokens.push_back(t); }

	// add a token to the (front of the) token stream
	// used by the lexer to add tokens to the token stream
	void addToken(Token t){ tokens.push_front(t); }

	// insert a token after the first token of the token stream
	// used by lex_identifier if another token is found
	void insertToken(Token t){ 
		std::deque<Token>::iterator it = tokens.begin();
		++it;
		tokens.insert(it, t);
	}
	
	// constructor for TokenStream
	TokenStream(){ }
	
	// get the number of token currently in the stream
	int getCount() { return tokens.size(); }
	
private:
	deque<Token> tokens;
};

#endif
