#include <string>

using namespace std;

// of type query_command :
const static string select = “select”;
const static string project = “project”;
const static string rename = “rename”;
const static string join = “JOIN”;
const static string union = “+”;
const static string difference = “-";
const static string product = “*”;

// of type db_command :
const static string close = “CLOSE”;
const static string create_table = “CREATE TABLE”;
const static string delete = “DELETE FROM”;
const static string exit = “EXIT”;
const static string insert = “INSERT INTO”;
const static string open = “OPEN”;
const static string primary_key = “PRIMARY KEY”
const static string set = “SET”;
const static string show = “SHOW”;
const static string update = “UPDATE”;
const static string values_from = “VALUES FROM”;
const static string values_from_relation = “VALUES FROM RELATION”;
const static string where = “WHERE”;
const static string write = “WRITE”;

//of type operator : 
const static string equals = “==”;
const static string not_equal = “!=”;
const static string less_than = “<”;
const static string less_equal = “<=”;
const static string arrow = “<-";
const static string greater_than = “>”;
const static string greater_equal = “>=”;
const static string or = “||”;
const static string and = “&&”;

/* other token types:
 * type			      ie. varchar(20)  or int
 * string_literal
 * int_literal
 * identifier
 * symbol		      can be open_paren, close_paren, or comma
*/

