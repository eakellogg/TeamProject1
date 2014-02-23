#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "Constants.h"
#include "TokenStream.h"

//Lex an inputted string
//skip spaces
TokenStream lex(std::string input);				//waiting for everything else

//if the symbol name is found, add the necessary token and return true, return false if not found
// works for: SELECT, PROJECT, RENAME, CLOSE, CREATE_TABLE,
//DELETE, INSERT, JOIN, OPEN, PRIMARY_KEY, SET, SHOW,
//UPDATE, VALUES_FROM, VALUES_FROM_RELATION, WHERE, WRITE, 
//UNION, DIFFERENCE, PRODUCT, OPEN_PAREN, COMMA
bool find_symbol(std::string& input, size_t& position, TokenStream& ts, std::string symbol_name);

//same functionality as find_symbol, but is safe for symbols at the end of the input
// works for: EXIT, CLOSE_PAREN
bool find_end_symbol(std::string& input, size_t& position, TokenStream& ts, std::string symbol_name);

//if "INTEGER" is found, add the necessary token and return true
bool find_int(std::string& input, size_t& position, TokenStream& ts);

//if "varchar(__)" is found, add the necessary token and return true
bool find_varchar(std::string& input, size_t& position, TokenStream& ts);


//function for lexing just things that arent alpha, digit, underscore???? --combining stuff centrally


//if "==" is found, add the necessary token and return true
bool find_equals(std::string& input, size_t& position, TokenStream& ts);
//when called throw error if false because "=" is not valid


//if "!=" is found, add the necessary token and return true
bool find_notEquals(std::string& input, size_t& position, TokenStream& ts);
//when called throw error if false because "!" is not valid


// if "<" was found, this function is called
// checks for "<=" then "<-" then "<" and adds correct token
void find_less(std::string& input, size_t& position, TokenStream& ts);


// if ">" was found, this function is called
// checks for ">=" then ">" and adds correct token
void find_greater(std::string& input, size_t& position, TokenStream& ts);


// if "||" was found, add the necessary token and return true
bool find_or(std::string& input, size_t& position, TokenStream& ts);
//when called, throw error if false because "|" is not valid


// if "&&" was found, add the necessary token and return true
bool find_and(std::string& input, size_t& position, TokenStream& ts);
//when called, throw error if false because "&" is not valid

// takes a string within quotation marks and adds the necessary token
bool find_string_literal(std::string& input, size_t& position, TokenStream& ts);

void find_int_literal(std::string& input, size_t& position, TokenStream& ts);

void lex_identifier(std::string& input, TokenStream& ts);
//well.............


//semicolon!!!


#endif












