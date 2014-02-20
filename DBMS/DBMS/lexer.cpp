
#include "Lexer.h"

using namespace std;



TokenStream lex(string input) {
	TokenStream ts;
	//case switch on first char while input not empty
	while (!input.empty() && (';' != input.front())) {

		char curr = input.front();
		size_t front = 0;
		switch (curr) {
		case 's':
			if (!find_symbol(input, front, ts, SELECT)) {
				lex_identifier(input, ts);
			}
			break;
		case 'p':
			if (!find_symbol(input, front, ts, PROJECT)) {
				lex_identifier(input, ts);
			}
			break;
		case 'r':
			if (!find_symbol(input, front, ts, RENAME)) {
				lex_identifier(input, ts);
			}
			break;
		//check for close then create table
		case 'C':
			if (!find_symbol(input, front, ts, CLOSE)) {
				if (!find_symbol(input, front, ts, CREATE_TABLE)) {
					lex_identifier(input, ts);
				}
			}
			break;
		case 'D':
			if (!find_symbol(input, front, ts, DELETE)) {
				lex_identifier(input, ts);
			}
			break;
		case 'E':
			if (!find_end_symbol(input, front, ts, EXIT)) {
				lex_identifier(input, ts);
			}
			break;
		//check for insert then integer
		case 'I':
			if (!find_symbol(input, front, ts, INSERT)) {
				if (!find_int(input, front, ts)) {
					lex_identifier(input, ts);
				}
			}
			break;
		case 'J':
			if (!find_symbol(input, front, ts, JOIN)) {
				lex_identifier(input, ts);
			}
			break;
		case 'O':
			if (!find_symbol(input, front, ts, OPEN)) {
				lex_identifier(input, ts);
			}
			break;
		case 'P':
			if (!find_symbol(input, front, ts, PRIMARY_KEY)) {
				lex_identifier(input, ts);
			}
			break;
		//check for set then show
		case 'S':
			if (!find_symbol(input, front, ts, SET)) {
				if (!find_symbol(input, front, ts, SHOW)) {
					lex_identifier(input, ts);
				}
			}
			break;
		case 'U':
			if (!find_symbol(input, front, ts, UPDATE)) {
				lex_identifier(input, ts);
			}
			break;
		//check for values from relation, then values from, then varchar
		case 'V':
			if (!find_symbol(input, front, ts, VALUES_FROM_RELATION)) {
				if (!find_symbol(input, front, ts, VALUES_FROM)) {
					if (!find_varchar(input, front, ts)) {
						lex_identifier(input, ts);
					}
				}
			}
			break;
		//check for where then write
		case 'W':
			if (!find_symbol(input, front, ts, WHERE)) {
				if (!find_symbol(input, front, ts, WRITE)) {
					lex_identifier(input, ts);
				}
			}
			break;
		case ' ':
			input.erase(input.begin());
			break;
		case '+':
			find_symbol(input, front, ts, UNION);
			break;
		case '-':
			if (isdigit(input.at(front + 1))) {
				find_int_literal(input, front, ts);
			}
			else {
				find_symbol(input, front, ts, DIFFERENCE);
			}
			break;
		case '*':
			find_symbol(input, front, ts, PRODUCT);
			break;
		//if it is '==' then add a symbol token, if it's only '=' then its the assignment operator
		case '=':
			if (!find_equals(input, front, ts)) {
				ts.addToken(Token(OPERATOR, ASSIGNMENT));
				input.erase(front, ASSIGNMENT.size());
			}
			break;
		case '!':
			if (!find_notEquals(input, front, ts)) {
				input.erase(front, front + 1);
				throw("'!' is an invalid entry");	//------------------------ I don't have a catch block in here
			}
			break;
		case '<':
			find_less(input, front, ts);
			break;
		case '>':
			find_greater(input, front, ts);
			break;
		case '|':
			if (!find_or(input, front, ts)) {
				input.erase(front, front + 1);
				throw("'|' is an invalid entry");	//-------------------------	samesies ^^
			}
			break;
		case '&':
			if (!find_and(input, front, ts)) {
				input.erase(front, front + 1);
				throw("'&' is an invalid entry");	//------------------------- samesies ^
			}
			break;
		case '(':
			find_symbol(input, front, ts, OPEN_PAREN);
			break;
		case ')':
			find_end_symbol(input, front, ts, CLOSE_PAREN);
			break;
		case ',':
			find_symbol(input, front, ts, COMMA);
			break;
		case '"':
			find_string_literal(input, front, ts);
			break;
		default:
			if (isalpha(curr))  {
				lex_identifier(input, ts);
			}
			else if (isdigit(curr)) {
				find_int_literal(input, front, ts);
			}
			else {
				input.erase(front, front + 1);
				throw("invalid input");
			}
			//have and error check here? I'm not sure what other characters there are, but still
			break;
		}
	}
	return ts;	
}

bool find_symbol(string& input, size_t& position, TokenStream& ts, string symbol_name) {
	if (symbol_name == input.substr(position, symbol_name.size())) {
		size_t next = position + symbol_name.size();
		if (input.at(next) != '_') {
			ts.addToken(Token(SYMBOL, symbol_name));
			input.erase(position, symbol_name.size());
			return true;
		}
		else {
			//if an underscore follows the symbol name, then it is assumed that it is inside of an identifier and it is not the command
			return false;
		}
	}
	else {
		return false;
	}
}

//This function does not check if the next char is an underscore, which could cause failure for symbols at the end of the line
bool find_end_symbol(string& input, size_t& position, TokenStream& ts, string symbol_name) {
	if (symbol_name == input.substr(position, symbol_name.size())) {
		size_t next = position + symbol_name.size();
		ts.addToken(Token(SYMBOL, symbol_name));
		input.erase(position, symbol_name.size());
		return true;
	}
	else {
		return false;
	}
}

bool find_int(string& input, size_t& position, TokenStream& ts) {
	if (INTEGER == input.substr(position, INTEGER.size())) {
		ts.addToken(Token(TYPE, INT_LITERAL));
		input.erase(position, INTEGER.size());
		return true;
	}
	else {
		return false;
	}
}


//so the value will be "VARCHAR(20)" or comprable string	//----------------------------
bool find_varchar(string& input, size_t& position, TokenStream& ts) {

	if (VAR_CHAR == input.substr(position, VAR_CHAR.size())) {
		size_t curr_pos = position + VAR_CHAR.size();
		size_t open_p = input.find('(', curr_pos);
		if (open_p == string::npos) {
			//no opening parenthesis found
			return false;
		}
		else {
			string value = VAR_CHAR + '(';
			while (isdigit(input.at(curr_pos))) {
				value += input.at(curr_pos);
				curr_pos = open_p + 1;
			}
			if (value.size() <= VAR_CHAR.size()) {
				//no digits inside the parenthesis found	//is this check needed?
				return false;
			}
			else {
				size_t close_p = input.find(')', curr_pos);
				curr_pos = close_p;
				if (close_p == string::npos) {
					//no closing parenthesis found
					return false;
				}
				else {
					value += ')';
					size_t space_used = curr_pos - position + 1; //may need to have a + 1 or -1 to do correctly
					ts.addToken(Token(TYPE, STRING_LITERAL));
					input.erase(position, space_used);
					return true;
				}
			}
		}
	}
	else {
		return false;
	}
}

bool find_equals(string& input, size_t& position, TokenStream& ts) {
	if (EQUALS == input.substr(position, EQUALS.size())) {
		ts.addToken(Token(OPERATOR, EQUALS));
		input.erase(position, EQUALS.size());
		return true;
	}
	else {
		return false;
	}
}

bool find_notEquals(string& input, size_t& position, TokenStream& ts) {
	if (NOT_EQUAL == input.substr(position, NOT_EQUAL.size())) {
		ts.addToken(Token(OPERATOR, NOT_EQUAL));
		input.erase(position, NOT_EQUAL.size());
		return true;
	}
	else {
		return false;
	}
}

void find_less(string& input, size_t& position, TokenStream& ts) {
	if (LESS_EQUAL == input.substr(position, LESS_EQUAL.size())) {
		ts.addToken(Token(OPERATOR, LESS_EQUAL));
		input.erase(position, LESS_EQUAL.size());
	}
	else if (ARROW == input.substr(position, ARROW.size())) {
		ts.addToken(Token(OPERATOR, ARROW));
		input.erase(position, ARROW.size());
	}
	else {
		ts.addToken(Token(OPERATOR, LESS_THAN));
		input.erase(position, LESS_THAN.size());
	}
}

void find_greater(string& input, size_t& position, TokenStream& ts) {
	if (GREATER_EQUAL == input.substr(position, GREATER_EQUAL.size())) {
		ts.addToken(Token(OPERATOR, GREATER_EQUAL));
		input.erase(position, GREATER_EQUAL.size());
	}
	else {
		ts.addToken(Token(OPERATOR, GREATER_THAN));
		input.erase(position, GREATER_THAN.size());
	}
}

bool find_or(string& input, size_t& position, TokenStream& ts) {
	if (OR == input.substr(position, OR.size())) {
		ts.addToken(Token(OPERATOR, OR));
		input.erase(position, OR.size());
		return true;
	}
	else {
		return false;
	}
}

bool find_and(string& input, size_t& position, TokenStream& ts) {
	if (AND == input.substr(position, AND.size())) {
		ts.addToken(Token(OPERATOR, AND));
		input.erase(position, AND.size());
		return true;
	}
	else {
		return false;
	}
}

bool find_string_literal(string& input, size_t& position, TokenStream& ts) {
	//pull "
	if (input.at(position) != '"') {
		//shouldn't happen because this function is only called if the current char is "
		return false;
	}
	size_t curr_pos = position + 1;	//to account for the "
	size_t end_quot = input.find('"', curr_pos);
	if (end_quot == string::npos) {
		//no ending quotation mark found
		return false;
	}
	else {
		size_t string_length = end_quot - curr_pos;	//check that this is correct
		string value = input.substr(curr_pos, string_length);
		size_t space_used = end_quot - position + 1;	//may need to have a + 1 or -1 to do correctly
		ts.addToken(Token(STRING_LITERAL, value));
		input.erase(position, space_used);
		return true;
	}
}

void find_int_literal(string& input, size_t& position, TokenStream& ts) {
	//currently we don't have support for negative ints because of set_difference
	//this could probably be fixed fairly easily
	size_t curr_pos = position;
	string value;

	//pull in the first char, - or digit
	value += input.at(curr_pos);
	++curr_pos;

	while (isdigit(input.at(curr_pos))) {
		value += input.at(curr_pos);
		++curr_pos;
	}
	ts.addToken(Token(INT_LITERAL, value));
	input.erase(position, value.size());
}

void lex_identifier(string& input, TokenStream& ts) {
	//and this is the complicated one...
	// isalnum = isalpha + isdigit
	size_t front = 0;
	size_t curr_pos = front;
	string value;
	while (isalnum(input.at(curr_pos)) || '_' == input.at(curr_pos)) {

		char c = input.at(curr_pos);
		switch (c) {
		case 's':
			if (find_symbol(input, curr_pos, ts, SELECT)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'p':
			if (find_symbol(input, curr_pos, ts, PROJECT)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'r':
			if (find_symbol(input, curr_pos, ts, RENAME)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'C':
			if (find_symbol(input, curr_pos, ts, CLOSE)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else if (find_symbol(input, curr_pos, ts, CREATE_TABLE)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'D':
			if (find_symbol(input, curr_pos, ts, DELETE)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'E':
			if (find_symbol(input, curr_pos, ts, EXIT)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'I':
			if (find_symbol(input, curr_pos, ts, INSERT)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else if (find_int(input, curr_pos, ts)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'J':
			if (find_symbol(input, curr_pos, ts, JOIN)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'O':
			if (find_symbol(input, curr_pos, ts, OPEN)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'P':
			if (find_symbol(input, curr_pos, ts, PRIMARY_KEY)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'S':
			if (find_symbol(input, curr_pos, ts, SHOW)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else if (find_symbol(input, curr_pos, ts, SET)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'U':
			if (find_symbol(input, curr_pos, ts, UPDATE)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'V':
			if (find_symbol(input, curr_pos, ts, VALUES_FROM)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else if (find_symbol(input, curr_pos, ts, VALUES_FROM)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else if (find_varchar(input, curr_pos, ts)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		case 'W':
			if (find_symbol(input, curr_pos, ts, WHERE)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else if (find_symbol(input, curr_pos, ts, WRITE)) {
				ts.insertToken(Token(IDENTIFIER, value));
				input.erase(front, value.size());
				return;
			}
			else {
				value += c;
			}
			break;
		default:
			value += c;
			break;
		}
		++curr_pos;

		if (curr_pos >= input.size())
		{
			break;
		}
	}
	ts.addToken(Token(IDENTIFIER, value));
	input.erase(front, value.size());
	return;
}
