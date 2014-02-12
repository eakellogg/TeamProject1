
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
const static string close = "CLOSE";
const static string create_table = "CREATE TABLE";
const static string deleted = "DELETE FROM";
const static string Exit = "EXIT";
const static string insert = "INSERT INTO";
const static string open = "OPEN";
const static string primary_key = "PRIMARY KEY";
const static string set = "SET";
const static string show = "SHOW";
const static string update = "UPDATE";
const static string values_from = "VALUES FROM";
const static string values_from_relation = "VALUES FROM RELATION";
const static string where = "WHERE";
const static string write = "WRITE";

const static string OPERATOR_TYPE = "OPERATOR";
//of type operator : 
const static string equals = "==";
const static string not_equal = "!=";
const static string less_than = "<";
const static string less_equal = "<=";
const static string greater_than = ">";
const static string greater_equal = ">=";
const static string or = "||";
const static string and = "&&";


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