#include "ConditionTree.h"

#include <iostream>
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
ConditionTree::Node::Node(Node& n){

	value = n.value;
	type = n.type;
	//parent can't happen

	for (int i = 0; i < n.children.size(); i++)
	{
		children.push_back(new Node(*n.children[i]));

	}
}
ConditionTree::Node::~Node(){

	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		if (children[i] != NULL)
			delete children[i];
	}
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
ConditionTree::ConditionTree(string type, string value){
	root = new Node(type, value, NULL);
}
ConditionTree::~ConditionTree(){
	delete root;
}
ConditionTree::ConditionTree(ConditionTree& t)
{
	root = new Node((*t.getRoot()));
}
ConditionTree::ConditionTree(Node* n){
	root = n;
}
ConditionTree::Node* ConditionTree::getRoot(){
	return root;
}