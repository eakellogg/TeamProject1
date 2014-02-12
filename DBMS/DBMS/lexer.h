#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;


const static string QUERY_COMMAND = "QUERY_COMMAND";
// of type query_command :
const static string select = "select";
const static string project = "project";
const static string rename = "rename";
const static string join = "JOIN";
const static string union = "+";
const static string difference = "-";
const static string product = "*";

const static string DB_COMMAND = "DB_COMMAND";
// of type db_command :
const static string close = "CLOSE";
const static string create_table = "CREATE TABLE";
const static string deleted = "DELETE FROM";
const static string exit = "EXIT";
const static string insert = "INSERT INTO";
const static string open = "OPEN";
const static string primary_key = "PRIMARY KEY";
const static string set = "SET";
const static string show = "SHOW";
const static string update = "UPDATE";
const static string VALUES_FROM = "VALUES FROM";
const static string VALUES_FROM_RELATION = "VALUES FROM RELATION";
const static string where = "WHERE";
const static string write = "WRITE";

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
