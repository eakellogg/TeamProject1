#ifndef EVALUATION_TREE_H
#define EVALUATION_TREE_H


#include <string>
#include <vector>
#include "Lexer.h"

//NODE TYPES
const static string PARSE_FAILURE = "PARSE_FAILURE";
const static string RELATION_NAME = "RELATION_NAME";
const static string EXPR = "EXPRESION";
const static string SELECTION = "SELECTION";
const static string PROJECTION = "PROJECTION";
const static string RENAMING = "RENAMING";
const static string UNION_EXPR = "UNION_EXPR";
const static string DIFFERENCE_EXPR = "DIFFERENCE_EXPR";
const static string PRODUCT_EXPR = "PRODCUT_EXPR";
const static string JOIN_EXPR = "JOIN_EXPR";
const static string CONDITION_TREE = "CONDITION_TREE";
const static string ATTRIBUTE_LIST = "ATTRIBUTE_LIST";
const static string ATTRIBUTE = "ATTRIBUTE";


const static string QUERY_OPERATOR = "QUERY_OPERATOR";
const static string COMMAND_OPERATOR = "COMMAND_OPERATOR";


//NODE VALUES
const static string PLACEMENT_SYMBOL = "<-";


class EvaluationTree{

public:
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