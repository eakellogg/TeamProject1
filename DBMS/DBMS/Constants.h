#pragma once


#include <string>
/*
This is the file with ALL CONSTANTS
It needs to be oraganized and commeneted on where needed
*/

using namespace std;

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

//of type query_command
const static string SELECT = "select";
const static string PROJECT = "project";
const static string RENAME = "rename";
const static string JOIN = "JOIN";
const static string UNION = "+";
const static string DIFFERENCE = "-";
const static string PRODUCT = "*";

const static string OPERATOR = "OPERATOR";
//of type operator : 
const static string ASSIGNMENT = "=";
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

const static string SYMBOL = "SYMBOL";
const static string TYPE = "TYPE";
const static string OPEN_PAREN = "(";
const static string CLOSE_PAREN = ")";
const static string COMMA = ",";
const static string SETT = "SET";
const static string STRING_LITERAL = "STRING_LITERAL";
const static string INT_LITERAL = "STRING_INT";


//NODE TYPES
const static string PARSE_FAILURE = "PARSE_FAILURE";
const static string RELATION_NAME = "RELATION_NAME";
const static string EXPR = "EXPRESION";
const static string SELECTION = "SELECTION";
const static string PROJECTION = "PROJECTION";
const static string RENAMING = "RENAMING";
const static string UNION_EXPR = "UNION_EXPR";
const static string DIFFERENCE_EXPR = "DIFFERENCE_EXPR";
const static string PRODUCT_EXPR = "PRODCUT_EXPR";
const static string JOIN_EXPR = "JOIN_EXPR";
const static string CONDITION_TREE = "CONDITION_TREE";
const static string ATTRIBUTE_LIST = "ATTRIBUTE_LIST";
const static string ATTRIBUTE = "ATTRIBUTE";



const static string QUERY_OPERATOR = "QUERY_OPERATOR";
const static string COMMAND_OPERATOR = "COMMAND_OPERATOR";
const static string ATTRIBUTE_TYPE_PAIR_LIST = "ATTRIBUTE_TYPE_PAIR_LIST";
const static string LITERAL_LIST = "LITERAL_LIST"; // vector< tuple<string , string> >*
const static string ATTRIBUTE_VALUE_PAIR_LIST = "ATTRIBTUE_VALUE_PAIR_LIST"; //vector< tuple<string, string> >*  attributename , value 

//NODE VALUES
const static string PLACEMENT_SYMBOL = "<-";



//TODO I SHOULD TYPE THIS
const std::string TABLE_MEMBER = "TABLE_MEMBER";
const std::string VARIABLE = "VARIBLE";


const std::string UNKNOWN = "UNKNOWN";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";

const std::string LESS = "<";
const std::string GREATER = ">";
const std::string LESSEQUAL = "<=";
const std::string GREATEREQUAL = ">=";
const std::string NOT = "!";