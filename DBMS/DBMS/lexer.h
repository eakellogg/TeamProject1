<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#ifndef LEXER_H
#define LEXER_H

#include <string>
=======
 #ifndef LEXER_H
 #define LEXER_H
 
#include <string>
#include "Constants.h"

>>>>>>> 7a0561666a8d64de68bae48f45c2ed8e11631541
using namespace std;
const static string DB_COMMAND = "DB_COMMAND";

<<<<<<< HEAD
// of type db_command :
=======
 #ifndef LEXER_H
 #define LEXER_H
 
const static string DB_COMMAND = "DB_COMMAND";

 // of type db_command :
>>>>>>> bba805f00c659f73faf70a3dd5311c333f19e447
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
<<<<<<< HEAD

//of type query_command
const static string SELECT = "select";
const static string PROJECT = "project";
const static string RENAME = "rename";
const static string JOIN = "JOIN";
const static string UNION = "+";
const static string DIFFERENCE = "-";
const static string PRODUCT = "*";

const static string OPERATOR_TYPE = "OPERATOR";
//of type operator :
const static string ASSIGNMENT = "=";
const static string EQUALS = "==";
const static string NOT_EQUAL = "!=";
const static string LESS_THAN = "<";
const static string LESS_EQUAL = "<=";
const static string ARROW = "<-";
const static string GREATER_THAN = ">";
const static string GREATER_EQUAL = ">=";
//const static string OR = "||";
//const static string AND = "&&";

const static string IDENTIFIER = "IDENTIFIER";

const static string TYPE = "TYPE";
const static string OPEN_PAREN = "(";
const static string CLOSE_PAREN = ")";
const static string COMMA = ",";
const static string SETT = "SET";
const static string STRING_LITERAL = "STRING_LITERAL";
const static string INT_LITERAL = "STRING_INT";

//other types that Ill type up later
/* other token types:
 * type			      ie. varchar(20)  or int
 * string_literal
 * int_literal
 * identifier
 * symbol		      can be open_paren, close_paren, or comma
 */
#endif
=======

=======
 #ifndef LEXER_H
 #define LEXER_H
 
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

>>>>>>> bba805f00c659f73faf70a3dd5311c333f19e447
=======
 #ifndef LEXER_H
 #define LEXER_H
 
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

>>>>>>> bba805f00c659f73faf70a3dd5311c333f19e447
//of type query_command
const static string SELECT = "select";
const static string PROJECT = "project";
 const static string RENAME = “rename”;
 const static string JOIN = “JOIN”;
 const static string UNION = “+”;
const static string DIFFERENCE = "-";
 const static string PRODUCT = “*”;

 const static string OPERATOR_TYPE = "OPERATOR";
 //of type operator : 
const static string EQUALS = "==";
const static string NOT_EQUAL = "!=";
const static string LESS_THAN = "<";
const static string LESS_EQUAL = "<=";
const static string ARROW = "<-";
const static string GREATER_THAN = ">";
const static string GREATER_EQUAL = ">=";
const static string OR = "||";
const static string AND = "&&";

 const static string IDENTIFIER = "IDENTIFIER";
 
 //other types that Ill type up later
  /* other token types:
  * type			      ie. varchar(20)  or int
  * string_literal
  * int_literal
  * identifier
  * symbol		      can be open_paren, close_paren, or comma
 */
 
 #endif
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> bba805f00c659f73faf70a3dd5311c333f19e447
=======
>>>>>>> bba805f00c659f73faf70a3dd5311c333f19e447
=======
>>>>>>> bba805f00c659f73faf70a3dd5311c333f19e447
=======
 
 #endif
>>>>>>> 7a0561666a8d64de68bae48f45c2ed8e11631541
