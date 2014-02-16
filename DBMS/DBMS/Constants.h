#pragma once


#include <string>
/*
This is the file with ALL CONSTANTS
*/

using namespace std;

const static string COMMAND_OPERATOR = "COMMAND_OPERATOR"; //Type of command

// Values for COMMAND_OPERATOR; they also are the value of symbols 
const static string CLOSE = "CLOSE";
const static string CREATE_TABLE = "CREATE TABLE";
const static string DELETE = "DELETE FROM";
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
//--------------------------------------------


const static string EXPR = "EXPRESION"; //Type of expression

//Values for EXPR Nodes
const static string SELECTION_EXPR = "SELECTION";
const static string PROJECTION_EXPR = "PROJECTION";
const static string RENAMING_EXPR = "RENAMING";
const static string UNION_EXPR = "UNION_EXPR";
const static string DIFFERENCE_EXPR = "DIFFERENCE_EXPR";
const static string PRODUCT_EXPR = "PRODUCT_EXPR";
const static string JOIN_EXPR = "JOIN_EXPR";
//--------------------------------------------


const static string OPERATOR = "OPERATOR"; //Type of operator

//Types of operators 
const static string EQUALS = "==";
const static string NOT_EQUAL = "!=";
const static string LESS_THAN = "<";
const static string LESS_EQUAL = "<=";
const static string ARROW = "<-";
const static string GREATER_THAN = ">";
const static string GREATER_EQUAL = ">=";
const static string OR = "||";
const static string AND = "&&";
//--------------------------------------------


//Values for operands when evaluated
const std::string VARIABLE = "VARIBLE";
const std::string UNKNOWN = "UNKNOWN";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";
//--------------------------------------------


const static string IDENTIFIER = "IDENTIFIER"; //Type of identifier
//And identifier can be any string


//---------------------------------------
const static string SYMBOL = "SYMBOL"; //Type of symbol

//values for symbols
const static string TYPE = "TYPE";
const static string OPEN_PAREN = "(";
const static string CLOSE_PAREN = ")";
const static string COMMA = ",";
const static string SETT = "SET";
const static string ASSIGNMENT = "=";
const static string SELECT = "select";
const static string PROJECT = "project";
const static string RENAME = "rename";
const static string JOIN = "JOIN";
const static string UNION = "+";
const static string DIFFERENCE = "-";
const static string PRODUCT = "*";
//---------------------------------------


//Literals
const static string STRING_LITERAL = "STRING_LITERAL";//Type
const static string INT_LITERAL    = "STRING_INT"; //Type
//Values can be any string
//--------------------------------------------


//NODE TYPES
const static string PARSE_FAILURE = "PARSE_FAILURE"; //Type any parse failure

const static string RELATION_NAME = "RELATION_NAME"; //Type
//A relation name can be any identifier

const static string QUERY = "QUERY"; //Type
//A query node will have two arguements, first a relation name, second an atomicExpression
//--------------------------------------------


//ConditionTree
const static string CONDITION_TREE = "CONDITION_TREE";

typedef vector< string > AttributeList;
const static string ATTRIBUTE_LIST = "ATTRIBUTE_LIST";

const static string ATTRIBUTE = "ATTRIBUTE";

typedef vector< tuple < string, string > > AttributeTypePairList; //type , name
const static string ATTRIBUTE_TYPE_PAIR_LIST = "ATTRIBUTE_TYPE_PAIR_LIST"; 

typedef vector< tuple< string, string > > LiteralList; //Type , value
const static string LITERAL_LIST = "LITERAL_LIST";

typedef vector< tuple< string, string> > AttributeValuePairList;   //attributename , value 
const static string ATTRIBUTE_VALUE_PAIR_LIST = "ATTRIBTUE_VALUE_PAIR_LIST"; 


