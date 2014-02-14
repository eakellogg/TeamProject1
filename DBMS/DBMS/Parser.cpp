#include "Parser.h"

#include <list>
#include <tuple>
#include <iostream>

typedef ConditionTree::Node Node;
EvaluationTree* parseQuery(TokenStream& ts){

	EvaluationTree::Node* leftChild = parseRelationName(ts);

	if (leftChild->getType() == RELATION_NAME)
	{

		string parentType = QUERY_OPERATOR;

		Token token = ts.getToken();
		if (token.getType() != PLACEMENT_SYMBOL)
		{
			//TODO
			//I'm not great with exceptions I need ideas
			//throw error;
		}

		string* value = new string(token.getValue());
		EvaluationTree::Node* root = new EvaluationTree::Node(NULL, QUERY_OPERATOR, (void*)value);

		root->addChild(leftChild);//----------------------------------------

		EvaluationTree::Node* rightChild = parseExpresion(ts);

		if (rightChild->getType() != EXPR){
			//TODO
			//THROW ERROR
		}

		root->addChild(rightChild); //--------------------------------------

		EvaluationTree* tree = new EvaluationTree(root);
		return tree;
	}
	else
	{
		EvaluationTree* tree = parseCommand(ts);
		if (tree->getRoot()->getType() == PARSE_FAILURE)
		{
			///FAILURE
		}
		return tree;
	}


}

EvaluationTree::Node* parseRelationName(TokenStream& ts){

	
	EvaluationTree::Node* result;

	Token t = ts.getToken();
	if ( t.getType() == IDENTIFIER ){
		
		string* relation_name = new string( t.getValue() );
		result = new EvaluationTree::Node(NULL,RELATION_NAME, (void*)(relation_name));
		return result;
	}
	else{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL ,PARSE_FAILURE, (void*)(new string("Couldn't parse an relation name")));
		return result;
	}
	
}

EvaluationTree::Node* parseExpresion(TokenStream& ts){

	EvaluationTree::Node* result;
	
	result = parseSelection(ts); //Try parsing a selection
	if (result->getType() == EXPR) 
		return result;
	delete result;
	
	result = parseProjection(ts); //Tyre parsing a projetion
	if (result->getType() == EXPR)
		return result;
	delete result;
	
	result = parseRenaming(ts); //Try parsing a rename
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseUnion(ts);
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseDifference(ts);
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseProduct(ts);
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseNaturalJoin(ts);
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseAtomicExpr(ts);
	if (result->getType() == EXPR)
		return result;
	else{

		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse an expresion");
		return result;
	}
}

EvaluationTree::Node* parseSelection(TokenStream& ts){

	EvaluationTree::Node* result;

	Token t = ts.getToken();
	if (t.getValue() != SELECT){
		
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse selection, no select token"));
		return result;
	}
	
	t = ts.getToken();
	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse selection, no ("));
		return result;
	}

	ConditionTree* condtree = parseConditionTree(ts);
	if (condtree->getRoot()->getType() == PARSE_FAILURE){
		delete condtree;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse a condition Tree "));
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != CLOSE_PAREN){
			ts.pushToken(t);
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse selection, no )"));
			return result;
	}
	EvalNodePointer leftChild = new EvalNode(NULL, CONDITION_TREE, (void*)(condtree));

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	
	if (rightChild->getType() == PARSE_FAILURE)
	{
		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, value);
		return result;
	}
	string* value = new string(SELECTION);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild); //---------------------------------------------
	result->addChild(rightChild); //--------------------------------------------
	
	return result;

}

EvalNodePointer parseProjection(TokenStream& ts){

	EvalNodePointer result;
	Token t = ts.getToken();
	if (t.getValue() != PROJECT){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse projection, no project"));
		return result;
	}

	t = ts.getToken();
	
	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse projection, no ("));
		return result;
	}

	EvalNodePointer leftChild = parseAttributeList(ts);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode( NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != CLOSE_PAREN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse projection, no )"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){
		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete rightChild;
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	string* value = new string(PROJECTION);
	result = new EvalNode(NULL, EXPR, (void*)value);//------------------------------
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------

}

EvalNodePointer parseRenaming(TokenStream& ts){

	EvalNodePointer result;
	Token t = ts.getToken();
	if (t.getValue() != RENAME){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse projection, no rename"));
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse renaming, no ("));
		return result;
	}

	EvalNodePointer leftChild = parseAttributeList(ts);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != CLOSE_PAREN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse renaming, no )"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){
		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete rightChild;
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	string* value = new string(RENAMING);
	result = new EvalNode(NULL, EXPR, (void*)value);//------------------------------
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------
}


EvalNodePointer parseUnion(TokenStream& ts){

	EvalNodePointer result;

	EvalNodePointer leftChild = parseAtomicExpr(ts);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue() != UNION){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse union, no UNION symbole"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	string* value = new string(UNION_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------
}


EvalNodePointer parseDifference(TokenStream& ts){
	
	EvalNodePointer result;

	EvalNodePointer leftChild = parseAtomicExpr(ts);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue() != DIFFERENCE){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse difference, no DIFFERENCE symbol"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE ){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	string* value = new string(DIFFERENCE_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------

}

EvalNodePointer parseProduct(TokenStream& ts){

	EvalNodePointer result;

	EvalNodePointer leftChild = parseAtomicExpr(ts);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue() != PRODUCT){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse PRODUCT, no PRODUCT symbol"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	string* value = new string(PRODUCT_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------

}

EvalNodePointer parseNaturalJoin(TokenStream& ts){

	EvalNodePointer result;

	EvalNodePointer leftChild = parseAtomicExpr(ts);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue() != JOIN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse natural join, no join symbol"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	string* value = new string(JOIN_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------

}

//Parse an Atomic-Expr
EvalNodePointer parseAtomicExpr(TokenStream& ts){

	EvalNodePointer result = NULL;
	
	result = parseRelationName(ts);
	if (result->getType() == RELATION_NAME){
		return result;
	}
	delete result;

	Token t = ts.getToken();
	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse atomic expr, no ("));
		return result;
	}

	result = parseExpresion(ts);
	if (result->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((result->getValue()))));
		delete result;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*) value);
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != CLOSE_PAREN){
		ts.pushToken(t);
		delete result;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse atomic expr, no )"));
		return result;
	}
	
	return result;
}
	


Node* parseOperand(TokenStream& ts){

	Node* result;
	Token t = ts.getToken();
	if (t.getType() == IDENTIFIER)
	{
		result = new Node(VARIABLE, t.getValue(), NULL);
		return result;
	}


	if ( (t.getType() == INT_LITERAL) || ( t.getType() == STRING_LITERAL ))
	{
		if (t.getType() == INT_LITERAL)
			result = new Node(INT_LITERAL, t.getValue(), NULL);
		else
			result = new Node(STRING_LITERAL, t.getValue(), NULL);
		
		return result;
	}

	ts.pushToken(t);

	result = new Node(PARSE_FAILURE, "No operand", NULL);
	return result;


}

Node* parseComparison(TokenStream& ts){

	Node* result = NULL;
	//TODO finish

	Token t = ts.getToken();
	if (t.getValue() == OPEN_PAREN)
	{
		result = parseDisjunction(ts);
		if (result->getType() != PARSE_FAILURE)
		{
			t = ts.getToken();
			if (t.getValue() == CLOSE_PAREN)
			{
				return result;
				
			}
			else
			{
				ts.pushToken(t);
				delete result;
				result = new Node(PARSE_FAILURE, "No )", NULL);
				return result;
			}

		}
		else
		{
			delete result;
			result = new Node(PARSE_FAILURE, "No condition", NULL);
			return result;
		}
	}
	else
	{
		ts.pushToken(t);
		Node* leftOp = parseOperand(ts);

		if (leftOp->getType() != PARSE_FAILURE)
		{

			Token t = ts.getToken();

			result = new Node(OPERATOR, t.getValue(), NULL);

			Node* rightOp = parseOperand(ts);
			if (rightOp->getType() == PARSE_FAILURE)
			{
				delete leftOp;
				delete result;
				result = new Node(PARSE_FAILURE, "NO right operand", NULL);
				return result;
			}

			result->addChild(leftOp);
			result->addChild(rightOp);
			return result;
		}

		delete leftOp;
		delete result;
		result = new Node(PARSE_FAILURE, "NO right operand", NULL);
		return result;
	}
}
Node*   parseConjunction(TokenStream& ts){

	Node* result = new Node(OPERATOR, AND, NULL);
	
	
	Node* node = parseComparison(ts);

	bool goOn = true;

	while ( goOn)
	{
		if (node->getType() == PARSE_FAILURE)
		{
			delete  node;
			goOn = false;
			break;
		}
		else
			result->addChild(node);

		Token t = ts.getToken();
		if (t.getValue() != AND){
			goOn = false;
			ts.pushToken(t);
			break;
		}
		else
			node = parseComparison(ts);
	}

	return result;
}
Node* parseDisjunction(TokenStream& ts){

	Node* node = new Node( OPERATOR, OR , NULL );
	
	
	Node* result = parseConjunction(ts);

	while (true)
	{

		if (result->getType() == PARSE_FAILURE)
		{
			delete node;
			break;
		}

		node->addChild(result);

		Token t = ts.getToken();
		if (t.getValue() != OR)
		{
			ts.pushToken(t);
			break;
		}
		result = parseConjunction(ts);

	}


	return node;

}



ConditionTree*        parseConditionTree(TokenStream& ts){


	Node* root = parseDisjunction(ts);
	ConditionTree* tree = new ConditionTree(root);

	return tree;
}


EvalNodePointer           parseAttributeList(TokenStream& ts){

	EvalNodePointer result;
	vector<string*>* attributelist = new vector<string*>();


	bool keepGoing = true;
	do{

		EvalNodePointer node = parseAttributeName(ts);

		if (node->getType() == PARSE_FAILURE){
			keepGoing = false;
		}
		else {
			attributelist->push_back(static_cast<string*>(node->getValue()));
		}

		Token t = ts.getToken();
		if (t.getValue() != COMMA ){

			ts.pushToken(t);
			keepGoing = false;
		}


	
	} while (keepGoing);
	result = new EvalNode(NULL, ATTRIBUTE_LIST, (void*)attributelist);
	return result;

}

EvalNodePointer           parseAttributeName(TokenStream& ts){

	EvalNodePointer result;
	Token t = ts.getToken();
	if (t.getType() != IDENTIFIER){

		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't attribute name not identifier"));
		return result;
	}

	string* value = new string(t.getValue());
	result = new EvalNode(NULL, ATTRIBUTE, value);
	return result;
}


EvaluationTree*    parseCommand(TokenStream& ts){

	EvaluationTree::Node* result;
	result = parseOpen(ts); //Try parsing a selection
	if (result->getType() == COMMAND_OPERATOR)
		return  new EvaluationTree(result);
	delete result;

	result = parseClose(ts); //Tyre parsing a projetion
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;

	result = parseWrite(ts); //Try parsing a rename
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;

	result = parseExit(ts);
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;

	result = parseShow(ts);
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;

	result = parseCreate(ts);
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;

	result = parseInsert(ts);
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;

	result = parseDelete(ts);
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	else{

		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse a command");
		return new EvaluationTree( result );
	}
}


EvalNodePointer    parseOpen(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != OPEN)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}

	string* value = new string(OPEN);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationNode);
	return result;
}


EvalNodePointer    parseClose(TokenStream& ts){
	
	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != CLOSE)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}


	string* value = new string(CLOSE);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationNode);
	return result;
}

EvalNodePointer    parseWrite(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != WRITE)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}


	string* value = new string(WRITE);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationNode);
	return result;
}

EvalNodePointer    parseExit(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != EXIT)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse open");
		return result;
	}

	string* value = new string(EXIT);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	return result;
}

EvalNodePointer    parseShow(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != SHOW)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse show");
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse show");
		return result;
	}


	string* value = new string(SHOW);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationNode);
	return result;
}

EvalNodePointer    parseCreate(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != CREATE_TABLE)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse create");
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse create");
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != OPEN_PAREN)
	{
		ts.pushToken(t);
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse create, no (");
		return result;
	}

	EvalNodePointer listNode = parseTypedAttributeList(ts);

	if (listNode->getType() == PARSE_FAILURE){
		delete relationNode;
		//string* value = new string( static_cast<string>( listNode->getValue() ) );
		delete listNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse create");
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != CLOSE_PAREN)
	{
		ts.pushToken(t);
		delete relationNode;
		delete listNode;
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, "Failed to parse create, no )");
		return result;
	}
	t = ts.getToken();
	if (t.getValue() != PRIMARY_KEY)
	{
		delete relationNode;
		delete listNode;
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no PRIMARY KEY");
		return result;
	}
	t = ts.getToken();
	if (t.getValue() != OPEN_PAREN)
	{
		delete relationNode;
		delete listNode;
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, (");
		return result;
	}

	EvalNodePointer attributeListNode = parseAttributeList(ts);
	if (attributeListNode->getType() == PARSE_FAILURE )
	{
		delete relationNode;
		delete listNode;
		delete attributeListNode;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}
	t = ts.getToken();
	if (t.getValue() != CLOSE_PAREN)
	{
		delete relationNode;
		delete listNode;
		delete attributeListNode;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no )");
		return result;
	}

	string* value = new string(SHOW);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationNode);
	result->addChild(listNode);
	result->addChild(attributeListNode);
	return result;
}

EvalNodePointer    parseUpdate(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != UPDATE){

		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

	EvalNodePointer relationName = parseRelationName(ts);
	if (relationName->getType() == PARSE_FAILURE){


		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != SETT){

		delete relationName;
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

	EvalNodePointer atrributeValuePairNode = parseAttributeValuePairNode(ts);
	if ( atrributeValuePairNode->getType() ==  PARSE_FAILURE){

		delete relationName;
		delete atrributeValuePairNode;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != WHERE){

		delete relationName;
		delete atrributeValuePairNode;
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

		ConditionTree* tree = parseConditionTree(ts);
		EvalNodePointer conditionNode = new EvalNode(NULL, CONDITION_TREE, (void*)tree);

	if (tree->getRoot()->getType() == PARSE_FAILURE){

		delete relationName;
		delete atrributeValuePairNode;
		delete conditionNode;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

	string* value = new string(UPDATE);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationName);
	result->addChild(atrributeValuePairNode);
	result->addChild(conditionNode);
	return result;
}

EvalNodePointer    parseInsert(TokenStream& ts){

	EvalNodePointer result = NULL;

	Token t = ts.getToken();
	if (t.getValue() != INSERT){

		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse Insert, no Insert");
		return result;
	}

	EvalNodePointer relationName = parseRelationName(ts);
	if (relationName->getType() == PARSE_FAILURE){
		delete relationName;

		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse insert, no relationName");
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != VALUES_FROM){

		ts.pushToken(t);
	}
	else{
		EvalNodePointer literalList = parseLiteralList(ts);
		if (literalList->getType() == PARSE_FAILURE){
			delete relationName;
			delete literalList;
			result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse insert, no literalList");
			return result;
		}
		
		string* value = new string(INSERT);
		result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
		result->addChild(relationName);
		result->addChild(literalList);
		return result;

	}

	t = ts.getToken();
	if (t.getValue() != VALUES_FROM_RELATION){

		ts.pushToken(t);
	}
	else{
		EvalNodePointer expr = parseExpresion(ts);
		if (expr->getType() == PARSE_FAILURE){
			delete relationName;
			delete expr;
			result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse insert, no expr");
			return result;
		}

		string* value = new string(INSERT);
		result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
		result->addChild(relationName);
		result->addChild(expr);


	}
	return result;

}


EvalNodePointer    parseDelete(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != DELETED){

		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse insert, no literalList");
		return result;
	}

	EvalNodePointer relationName = parseRelationName(ts);
	if (relationName->getType() == PARSE_FAILURE){
		delete relationName;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse insert, no expr");
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != WHERE){

		ts.pushToken(t);
		delete relationName;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse delete, no WHERE");
		return result;
	}

	ConditionTree* tree = parseConditionTree(ts);
	EvalNodePointer conditionNode = new EvalNode(NULL, CONDITION_TREE, (void*)tree);

	if (tree->getRoot()->getType() == PARSE_FAILURE){

		delete relationName;
		delete conditionNode;
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse create, no attibuteList");
		return result;
	}

	string* value = new string(DELETED);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationName);
	result->addChild(conditionNode);
	return result;

}

EvalNodePointer    parseTypedAttributeList(TokenStream& ts){

	EvalNodePointer result;
	vector< tuple<string* , string*> >* attributetypelist = new vector< tuple<string* , string*> >();


	bool keepGoing = true;
	do{

		EvalNodePointer node = parseAttributeName(ts);
		EvalNodePointer type = parseType(ts);

		if (node->getType() == PARSE_FAILURE){
			keepGoing = false;
		}
		else {

			string* valueAtt = static_cast<string*>(node->getValue());
			string* valueType = static_cast<string*> (type->getValue());

			attributetypelist->push_back( make_tuple( valueAtt , valueType  ));
		}

		Token t = ts.getToken();
		if (t.getValue() != COMMA){

			ts.pushToken(t);
			keepGoing = false;
		}



	} while (keepGoing);
	result = new EvalNode(NULL, ATTRIBUTE_TYPE_PAIR_LIST, (void*)attributetypelist);
	return result;
}

EvalNodePointer    parseType(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getType() != TYPE){

		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, "Failed to parse type, no type");
		return result;
	}

	string* value = new string(t.getValue());
	result = new EvalNode(NULL, TYPE, value);
	return result;
}

EvalNodePointer    parseAttributeValuePairNode(TokenStream& ts){

	EvalNodePointer result;

	vector< tuple<string, string> >* list = new vector< tuple<string, string>>();

	Token t1 = ts.getToken();
	Token t2 = ts.getToken();
	Token t3 = ts.getToken();
	while ( (t1.getType() == IDENTIFIER) && (t2.getValue() == ASSIGNMENT) && (t3.getType() == INT_LITERAL || 
		t3.getType() == STRING_LITERAL)){

		list->push_back(make_tuple(t1.getValue(), t3.getValue()));
		 t1 = ts.getToken();
		 t2 = ts.getToken();
		 t3 = ts.getToken();
	}
	if (t3.getType() != FILLER)
		ts.pushToken(t3);
	if (t2.getType() != FILLER)
		ts.pushToken(t2);
	ts.pushToken(t1);


	result = new EvalNode(NULL, ATTRIBUTE_VALUE_PAIR_LIST, (void*)list);
	return result;
}
EvalNodePointer    parseLiteralList(TokenStream& ts){

	vector< tuple<string , string> >* list = new vector<tuple<string ,string> >(); //Strings inside don't need to be pointers

	EvalNodePointer result;

	Token t = ts.getToken();
	bool continueON = true;
	while ( (t.getType() == STRING_LITERAL || t.getType() == INT_LITERAL) && continueON) //Make this standard
	{

		string type(t.getType());
		string value(t.getValue());

		list -> push_back(make_tuple(type, value));
		
		t = ts.getToken();

		if (t.getValue() != COMMA){

			ts.pushToken(t);
			continueON = false;
		}
		else
			t = ts.getToken();

	}

	result = new EvalNode(NULL, LITERAL_LIST, (void*)list);
	return result;

}