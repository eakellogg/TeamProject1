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