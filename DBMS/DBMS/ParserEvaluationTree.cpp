

#include "EvaluationTree.h"


//---------------------------------------
/*      EvaluationTree::Node methods*/

EvaluationTree::Node::Node(Node* parent, string type, void* value){

	this->parent = parent;
	this->type = type;
	this->value = value;
}
void EvaluationTree::Node::setParent(Node* parent){
	this->parent = parent;
}
EvaluationTree::Node* EvaluationTree::Node::getParent(){
	return parent;
}
vector<EvaluationTree::Node*>* EvaluationTree::Node::getChildren(){
	return &children;
}
void* EvaluationTree::Node::getValue(){
	return value;
}
string EvaluationTree::Node::getType(){
	return type;
}
void  EvaluationTree::Node::addChild(string type, void* value){
	children.push_back( new Node( this , type, value));
}
void  EvaluationTree::Node::addChild(Node* child){
	child->setParent(this);
	children.push_back(child);
}

//-------------------------------------
/* EvaluationTree methods */

EvaluationTree::Node* EvaluationTree::getRoot(){
	return root;
}
EvaluationTree::EvaluationTree(Node* root){
	this->root = root;
}


