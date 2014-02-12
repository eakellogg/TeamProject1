#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;


const static string QUERY_COMMAND = "QUERY_COMMAND";
// of type query_command :
const static string SELECT = "select";
const static string PROJECT = "project";
const static string RENAME = "rename";
const static string JOIN = "JOIN";
const static string UNION = "+";
const static string DIFFERENCE = "-";
const static string PRODUCT = "*";

const static string DB_COMMAND = "DB_COMMAND";
// of type db_command :
const static string CLOSE = "CLOSE";
const static string CREATE_TABLE = "CREATE TABLE";
const static string DELETED = "DELETE FROM";
const static string EXIT = "EXIT";
const static string INSERT = "INSERT INTO";
const static string OPEN = "OPEN";
const static string PRIMARY_KEY = "PRIMARY KEY";
const static string SET = "SET";
const static string SHOW = "SHOW";
const static string UPDATE = "UPDATE";
const static string VALUES_FROM = "VALUES FROM";
const static string VALUES_FROM_RELATION = "VALUES FROM RELATION";
const static string WHERE = "WHERE";
const static string WRITE = "WRITE";

const static string OPERATOR_TYPE = "OPERATOR";
//of type operator : 
const static string EQUALS = "==";
const static string NOT_EQUAL = "!=";
const static string LESS_THAN = "<";
const static string LESS_EQUAL = "<=";
const static string GREATER_THAN = ">";
const static string GREATER_EQUAL = ">=";
const static string OR = "||";
const static string AND = "&&";


const static string IDENTIFIER = "IDENTIFIER";
const static string SYMBOL = "SYMBOL";
const static string OPEN_PAREN = "(";
const static string CLOSE_PAREN = ")";
const static string COMMA = ",";
/* other token types:
 * type			      ie. varchar(20)  or int
 * string_literal
 * int_literal
 * identifier
 * symbol		      can be open_paren, close_paren, or comma
*/

#endif
