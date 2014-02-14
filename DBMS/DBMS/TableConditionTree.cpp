#include "ConditionTree.h"

using namespace std;


//-----------------------------------------
/* Node Methods
*/
//-----------------------------------------
ConditionTree::Node::Node(string t, string v, Node* p){
	
	value  = v;
	type   = t;
	parent = p;
}
ConditionTree::Node::~Node(){

	for (int i = 0; i < children.size(); i++)
		delete children[i];
}

string ConditionTree::Node::getValue() const { return value; }
string ConditionTree::Node::getType() const  { return type;  }
ConditionTree::Node* ConditionTree::Node::getParent() const { return parent; }


ConditionTree::Node* ConditionTree::Node::addChild(string type, string value){

	ConditionTree::Node* node = new ConditionTree::Node(type , value,  this);
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
ConditionTree::~ConditionTree(){
	delete root;
}
ConditionTree::ConditionTree(Node* n){
	root = n;
}
ConditionTree::Node* ConditionTree::getRoot(){
	return root;
}