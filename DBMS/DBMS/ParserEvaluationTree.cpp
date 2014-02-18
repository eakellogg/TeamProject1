
#include "EvaluationTree.h"

#include <iostream>
using namespace std;
//---------------------------------------
/*      EvaluationTree::Node methods*/

// constructor for EvaluationTree::Node
EvaluationTree::Node::Node(Node* parent, string type, void* value){

	this->parent = parent;
	this->type = type;
	this->value = value;
}

// destructor for EvaluationTree::Node
EvaluationTree::Node::~Node(){
	/*
	if (value != NULL)
		delete value;
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] != NULL)
			delete children[i];
	}
	*/
}

// set the parent of the node
void EvaluationTree::Node::setParent(Node* parent){
	this->parent = parent;
}

// get the parent of the node
EvaluationTree::Node* EvaluationTree::Node::getParent(){
	return parent;
}

// get the children of the node
vector<EvaluationTree::Node*>* EvaluationTree::Node::getChildren(){
	return &children;
}

// get the value of the node
void* EvaluationTree::Node::getValue(){
	return value;
}

// get the type of the node
string EvaluationTree::Node::getType(){
		return type;
}

// add a child to the node based on type and value
void  EvaluationTree::Node::addChild(string type, void* value){
	children.push_back( new Node( this , type, value));
}

// add a child to the node based on pointer to a node
void  EvaluationTree::Node::addChild(Node* child){
	child->setParent(this);
	children.push_back(child);
}

//-------------------------------------
/* EvaluationTree methods */

// get the root of the evaluation tree
EvaluationTree::Node* EvaluationTree::getRoot(){
	return root;
}

// constructor for the evaluation tree
EvaluationTree::EvaluationTree(Node* root){
	this->root = root;
}

// destructor for the evaluation tree
EvaluationTree::~EvaluationTree(){
	//if ( root!= NULL)
		//delete root;
}
