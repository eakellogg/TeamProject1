#ifndef EVALUATION_TREE_H
#define EVALUATION_TREE_H


#include <string>
#include <vector>
#include "Lexer.h"



class EvaluationTree{

public:
	~EvaluationTree();
	class Node{

	public:
		Node(Node* parent, string type, void* value);
		Node* getParent();
		vector<Node*>* getChildren();
		void* getValue();
		string getType();
		void  addChild(string type, void* value);
		void  addChild(Node* n);
		void  setParent(Node* parent);
		~Node();
	private:
		Node* parent;
		vector<Node*> children;
		void* value;
		string type;

	};

	EvaluationTree(Node* root);
	Node* getRoot();

private:
	Node* root;


};

#endif EVALUATION_TREE_H