


#include "ConditionTree.h"

using namespace std;


//-----------------------------------------
/* Node Methods
*/
//-----------------------------------------
ConditionTree::Node::Node(string v, string t, Node* p){
	
	value  = v;
	type   = t;
	parent = p;
	leftChild  = NULL;
	rightChild = NULL;

}

string ConditionTree::Node::getValue() const { return value; }
string ConditionTree::Node::getType() const  { return type;  }
ConditionTree::Node* ConditionTree::Node::getParent() const { return parent; }
ConditionTree::Node* ConditionTree::Node::getLeftChild() const { return leftChild; }
ConditionTree::Node* ConditionTree::Node::getRightChild() const { return rightChild; }

ConditionTree::Node* ConditionTree::Node::setLeftChild( string v, string t){
	
	leftChild = new Node(v, t, this);
	return leftChild;
}

ConditionTree::Node* ConditionTree::Node::setRightChild(string v, string t){

	rightChild = new Node(v, t, this);
	return rightChild;
}


//-----------------------------
//ConditionTree Methods
//----------------------------
ConditionTree::ConditionTree(string value, string type){
	root = new Node(value, type, NULL);
}

ConditionTree::Node* ConditionTree::getRoot(){
	return root;
}




/*
class ConditionTree
{
public:
	class Node
	{
	private:
		std::string value;
		std::string type; //Is the value a literal (string or int), operand , or table type
		Node*       leftChild;
		Node*       rightChild;
		Node*       parent;
	public:
		Node(std::string value, std::string type, Node* parent);
		std::string getValue()     const;
		std::string getType()      const;
		Node*       getParent()    const;
		Node*       getLeftChild() const;
		Node*       getRightChild()const;
		void        setLeftChild(Node* n);
		void        setRightChilde(Node* n);
		void        setParent(Node* n);
	};

private:
	Node* root;
public:
	ConditionTree();

	Node* getRoot();

};

*/