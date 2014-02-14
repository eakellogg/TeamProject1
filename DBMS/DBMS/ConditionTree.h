 #ifndef COND_TREE_H
#define COND_TREE_H

#include <string>
#include <vector>

//TODO I SHOULD TYPE THIS
const std::string OPERATOR     = "OPERATOR";
const std::string TABLE_MEMBER = "TABLE_MEMBER";
const std::string LITERAL_STRING      = "LITERAL_STRING";
const std::string LITERAL_INT = "LITERAL_INT";
const std::string VARIABLE = "VARIBLE";

const std::string FAILURE = "ERROR";

const std::string UNKNOWN = "UNKNOWN";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";

const std::string EQUAL = "=";
const std::string LESS = "<";
const std::string GREATER = ">";
const std::string LESSEQUAL = "<=";
const std::string GREATEREQUAL = ">=";
const std::string AND = "&&";
const std::string OR = "||";
const std::string NOT = "!";

class ConditionTree
{
public:
	class Node
	{
	private:
		std::string value;    
		std::string type; //Is the value a literal (string or int), operand , or table type
		std::vector<Node*> children;
		Node*       parent;

	public:
		Node(std::string value, std::string type, Node* parent);
		std::string getValue()     const;
		std::string getType()      const;
		Node*       getParent()    const;
		Node*       addChild(std::string v, std::string t);
		Node*       addChild(Node* n);
		//Node*     setParent(std::string v, std::string t);
		std::vector<Node*> getChildern();
	};

private:
	Node* root;
public:
	ConditionTree( std::string value , std::string type);
	ConditionTree(Node* n);
	Node* getRoot();
	//Node* setRoot( std::string v , std::string t)
};

#endif