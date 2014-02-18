 #ifndef COND_TREE_H
#define COND_TREE_H

#include <string>
#include <vector>
#include "Constants.h"
//TODO I SHOULD TYPE THIS
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
		Node( std::string type, std::string value, Node* parent );
		Node(Node& n);
		std::string getValue()     const;
		std::string getType()      const;
		Node*       getParent()    const;
		Node*       addChild(std::string t, std::string v);
		Node*       addChild(Node* n);
		//Node*     setParent(std::string v, std::string t);
		std::vector<Node*> getChildern();
		~Node();
	};

private:
	Node* root;
public:
	ConditionTree( std::string value , std::string type);
	ConditionTree(ConditionTree& t);
	ConditionTree(Node* n);
	Node* getRoot();
	//Node* setRoot( std::string v , std::string t)
	~ConditionTree();
};

#endif