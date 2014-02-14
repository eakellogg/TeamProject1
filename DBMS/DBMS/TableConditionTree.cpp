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
	children.push_back(NULL);
	children.push_back(NULL);
}

string ConditionTree::Node::getValue() const { return value; }
string ConditionTree::Node::getType() const  { return type;  }
ConditionTree::Node* ConditionTree::Node::getParent() const { return parent; }


ConditionTree::Node* ConditionTree::Node::addChild(string value, string type){

	ConditionTree::Node* node = new ConditionTree::Node(value, type , this);
	children.push_back(node);
	return node;

}
ConditionTree::Node* ConditionTree::Node::addChild(Node* n){

	children.push_back(n);
	return n;

}
std::vector<ConditionTree::Node*> ConditionTree::Node::getChildern(){
	return children;
}
//-----------------------------
//ConditionTree Methods
//----------------------------
ConditionTree::ConditionTree(string value, string type){
	root = new Node(value, type, NULL);
}
ConditionTree::ConditionTree(Node* n){
	root = n;
}
ConditionTree::Node* ConditionTree::getRoot(){
	return root;
}