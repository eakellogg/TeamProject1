#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <iostream>
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
	// get a token from the token stream
	Token getToken(){
		if (tokens.size() != 0){
			Token t = tokens[tokens.size() - 1]; tokens.pop_back();  return t;
		}
		else return Token(FILLER, "NOTHING HERE");
	}
	
	// push a token into the token stream
	void pushToken(Token t){ tokens.push_back(t); }
	
	// constructor for TokenStream
	TokenStream(){ index = 0; }
	
	// get the number of token currently in the stream
	int getCount() { return tokens.size(); }
	
private:
	vector<Token> tokens;
	int index;
};

#endif
