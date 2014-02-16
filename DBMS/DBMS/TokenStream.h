
#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <iostream>
using namespace std;
const static string FILLER = "FILLER";
class Token{
public:
	string getValue(){
		return value;
	}
	string getType(){
		return type;
	}
	Token( string type, string value) : value(value), type(type){}
private:
	string value;
	string type;

};
class TokenStream{

public:
	Token getToken(){
		if (tokens.size() != 0){
			Token t = tokens[tokens.size() - 1]; tokens.pop_back();  return t;
		}
		else return Token(FILLER, "NOTHING HERE");
				}
	void  pushToken(Token t){ tokens.push_back(t); }
	TokenStream(){ index = 0; }
	int  getCount() { return tokens.size(); }
private:
	vector<Token> tokens;
	int index;
};

#endif