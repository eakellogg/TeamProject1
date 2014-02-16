#include "Parser.h"

#include <list>
#include <tuple>
#include <iostream>

typedef ConditionTree::Node Node;


// parse a query, return an evaluation tree pointer
EvaluationTree* parseQuery(TokenStream& ts){

	EvaluationTree::Node* leftChild = parseRelationName(ts);
	EvaluationTree::Node* root;

	// if leftChild is a relation
	if (leftChild->getType() == RELATION_NAME)
	{
		Token token = ts.getToken();
		
		// if token is not an arrow
		if (token.getValue() != ARROW)
		{	
			ts.pushToken(token);
			delete leftChild;
			string* value = new string("No arrow found, failed to parse query");
			root = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return new EvaluationTree(root); // return the failure
		}
		else
		{
			string* value = new string( token.getValue() );
			root = new EvaluationTree::Node(NULL, QUERY, (void*)value);
			
			EvaluationTree::Node* rightChild = parseExpresion(ts);
			
			// if token is not an expression
			if (rightChild->getType() != EXPR)
			{
				delete leftChild;
				delete rightChild;
				string* value = new string("No expr found for right argument of query");
				root = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
				return new EvaluationTree(root); // return the failure
			}
			else
			{
				root->addChild(leftChild);//----------------------------------------
				root->addChild(rightChild); //--------------------------------------
				EvaluationTree* tree = new EvaluationTree(root);
				return tree; // return the tree to be evaluated
			}
		}
	}
	else
	{
		delete leftChild;

		EvaluationTree* tree = parseCommand(ts);
		
		// if the type of the passed tree is failure
		if ( tree->getRoot()->getType() == PARSE_FAILURE)
		{
			delete tree;
			string* value = new string("No query found, then no command found parse failure");
			root = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return new EvaluationTree(root); // return the failure

		}
		else
			return tree; // return the tree to be evaluated
	}
	return NULL;
}


// parse a relation, return a node pointer
EvaluationTree::Node* parseRelationName(TokenStream& ts){
	
	EvaluationTree::Node* result;
	Token t = ts.getToken();
	
	// if the token is an identifier
	if ( t.getType() == IDENTIFIER ){
		
		string* relation_name = new string( t.getValue() );
		result = new EvaluationTree::Node(NULL, RELATION_NAME, (void*)(relation_name));
		return result; // return the tree to be evaluated
	}
	else{
		ts.pushToken(t);
		string* value = new string("Couldn't parse an relation name");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result; // return the failure
	}
	
}


// parse an expression, return a node pointer
EvaluationTree::Node* parseExpresion(TokenStream& ts){

	EvaluationTree::Node* result;
	
	result = parseSelection(ts); //Try parsing a selection
	if (result->getType() == EXPR) 
		return result;
	delete result;
	
	result = parseProjection(ts); //Try parsing a projetion
	if (result->getType() == EXPR)
		return result;
	delete result;
	
	result = parseRenaming(ts); //Try parsing a rename
	if (result->getType() == EXPR)
		return result;
	delete result;
	
	result = parseUnion(ts); //Try parsing a union
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseDifference(ts); //Try parsing a difference
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseProduct(ts); //Try parsing a product
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseNaturalJoin(ts); //Try parsing a natural join
	if (result->getType() == EXPR)
		return result;
	delete result;

	result = parseAtomicExpr(ts); //Try parsing an atomic expression
	if (result->getType() == EXPR)
		return result;
		
	else{
		string* value = new string("failed to parse an expresion");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, value);
		return result; // return the failure
	}
}


// parse a selection, return a node pointer
EvaluationTree::Node* parseSelection(TokenStream& ts){

	EvaluationTree::Node* result;
	Token t = ts.getToken();
	
	// if the token does not equal select
	if (t.getValue() != SELECT){
		ts.pushToken(t);
		string* value = new string("Couldn't parse selection, no select token");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result; // return the failure
	}
	
	t = ts.getToken();

	// if the token does not equal an open parentheses
	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		string* value = new string("Couldn't parse selection, no (");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result; // return the failure
	}

	ConditionTree* condtree = parseConditionTree(ts);
	
	// if the type of the passed tree is failure
	if (condtree->getRoot()->getType() == PARSE_FAILURE){
		delete condtree;
		string* value = new string("Couldn't parse selection, no condition");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result; // return the failure
	}

	t = ts.getToken();

	// if the token does not equal a close parentheses
	if (t.getValue() != CLOSE_PAREN){
			ts.pushToken(t);
			string* value = new string("Couldn't parse selection, no )");
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return result; // return the failure
	}
	
	EvalNodePointer leftChild = new EvalNode(NULL, CONDITION_TREE, (void*)(condtree));
	EvalNodePointer rightChild = parseAtomicExpr(ts);

	// if the type of the child is failure
	if (rightChild->getType() == PARSE_FAILURE)
	{
		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, value);
		return result; // return the failure
	}
	
	string* value = new string(SELECTION_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild); 
	result->addChild(rightChild);
	return result; // return the node
}


// parse a projection, return a node pointer
EvalNodePointer parseProjection(TokenStream& ts){

	EvalNodePointer result;
	Token t = ts.getToken();
	//cout << "Inside projection found a " << t.getValue() << endl;
	if (t.getValue() != PROJECT){
		ts.pushToken(t);
		string* value = new string("Couldn't parse projection, no project");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();
	//cout << "inside projection looking for a ( found a" << t.getValue() << endl;
	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		string* value = new string("Couldn't parse projection, no (");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer leftChild = parseAttributeList(ts);
	//cout << "Inside projection looked for a attribute list found a " << leftChild->getType() << endl;
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode( NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();
	//cout << "Inside projection looking for ) found " << t.getValue() << endl;
	if (t.getValue() != CLOSE_PAREN){
		ts.pushToken(t);
		string* value = new string("Couldn't parse projection, no )");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	//cout << "inside projeciont looking for atomic expr found a " << rightChild->getType() << endl;
	if (rightChild->getType() == PARSE_FAILURE){
		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete rightChild;
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	string* value = new string(PROJECTION_EXPR);
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
		string* value = new string("Couldn't parse projection, no rename");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != OPEN_PAREN){
		ts.pushToken(t);
		string* value = new string("Couldn't parse projection, no (");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
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
		string* value = new string("Couldn't parse projection, no )");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
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

	string* value = new string(RENAMING_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);//------------------------------
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------
}


EvalNodePointer parseUnion(TokenStream& ts){

	EvalNodePointer result;
	
	TokenStream copyTS = ts;

	EvalNodePointer leftChild = parseAtomicExpr(copyTS);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = copyTS.getToken();
	if (t.getValue() != UNION){
		copyTS.pushToken(t);
		string* value = new string("Couldn't parse union, no UNION symbol");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(copyTS);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	ts = copyTS;
	string* value = new string(UNION_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------
}


EvalNodePointer parseDifference(TokenStream& ts){
	
	EvalNodePointer result;
	TokenStream copyTS = ts;
	EvalNodePointer leftChild = parseAtomicExpr(copyTS);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = copyTS.getToken();
	if (t.getValue() != DIFFERENCE){
		copyTS.pushToken(t);
		string* value = new string("Couldn't parse difference, no DIFFERENCE symbol");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(copyTS);
	if (rightChild->getType() == PARSE_FAILURE ){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	ts = copyTS;
	string* value = new string(DIFFERENCE_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------

}

EvalNodePointer parseProduct(TokenStream& ts){

	EvalNodePointer result;
	TokenStream copyTS = ts;
	EvalNodePointer leftChild = parseAtomicExpr(copyTS);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = copyTS.getToken();
	if (t.getValue() != PRODUCT){
		copyTS.pushToken(t);
		string* value = new string("Couldn't parse PRODUCT, no PRODUCT symbol");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(copyTS);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	ts = copyTS;
	string* value = new string(PRODUCT_EXPR);
	result = new EvalNode(NULL, EXPR, (void*)value);
	result->addChild(leftChild);//---------------------
	result->addChild(rightChild);//-----------------------------------
	return result;//------------------------------------------

}

EvalNodePointer parseNaturalJoin(TokenStream& ts){

	EvalNodePointer result;
	TokenStream copyTS = ts;
	EvalNodePointer leftChild = parseAtomicExpr(copyTS);
	if (leftChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((leftChild->getValue()))));
		delete leftChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	Token t = copyTS.getToken();
	if (t.getValue() != JOIN){
		copyTS.pushToken(t);
		string* value = new string("Couldn't parse natural join, no join symbol");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)(value));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(copyTS);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}


	ts = copyTS;
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
	string* value = static_cast<string*>(result->getValue());
	if (result->getType() != RELATION_NAME){

		string* value = new string((*static_cast<string*>((result->getValue()))));
		delete result;
	}
	else
		return result;


	Token t = ts.getToken();
	if (t.getValue() != OPEN_PAREN){

		ts.pushToken(t);
		string* value = new string("");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

		result = parseExpresion(ts);
		
		if (result->getType() == PARSE_FAILURE){

			string* value = new string((*static_cast<string*>((result->getValue()))));
			delete result;
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return result;
		}

		t = ts.getToken();
		if (t.getValue() != CLOSE_PAREN){

			ts.pushToken(t);
			string* value = new string((*static_cast<string*>((result->getValue()))));
			delete result;
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return result;
		}
		else
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
	vector<string>* attributelist = new vector<string>();


	bool keepGoing = true;
	do{

		EvalNodePointer node = parseAttributeName(ts);

		if (node->getType() == PARSE_FAILURE){
			delete node;
			keepGoing = false;
		}
		else {
			attributelist->push_back((*static_cast<string*>(node->getValue())));
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

	EvalNodePointer result = NULL;
	
	
	result = parseOpen(ts); //Try parsing a Open
	if (result->getType() == COMMAND_OPERATOR)
		return  new EvaluationTree(result);
	delete result;

	result = parseClose(ts); //Try parsing a Close
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;
	result = parseWrite(ts); //Try parsing a Write
	if (result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	delete result;
	result = parseExit(ts); //Try parsing an Exit
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
	if (  result->getType() == COMMAND_OPERATOR)
		return new EvaluationTree( result );
	else{
		
		delete result;
		string* value = new string("failed to parse a command");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return new EvaluationTree( result );
	}
}


EvalNodePointer    parseOpen(TokenStream& ts){

	EvalNodePointer result;

	Token t = ts.getToken();
	if (t.getValue() != OPEN)
	{
		ts.pushToken(t);
		string* value = new string("Failed to parse open");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value );
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		string* value = new string("Failed to parse open");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse close");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		string* value = new string("Failed to parse close");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse write");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		
		delete relationNode;
		string* value = new string("Failed to parse write");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse Exit");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse show");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		string* value = new string("Failed to parse show");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer relationNode = parseRelationName(ts);
	if (relationNode->getType() == PARSE_FAILURE){
		delete relationNode;
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != OPEN_PAREN)
	{
		ts.pushToken(t);
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer listNode = parseTypedAttributeList(ts);

	if (listNode->getType() == PARSE_FAILURE){
		delete relationNode;
		//string* value = new string( static_cast<string>( listNode->getValue() ) );
		delete listNode;
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != CLOSE_PAREN)
	{
		ts.pushToken(t);
		delete relationNode;
		delete listNode;
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}
	t = ts.getToken();
	if (t.getValue() != PRIMARY_KEY)
	{
		delete relationNode;
		delete listNode;
		ts.pushToken(t);
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}
	t = ts.getToken();
	if (t.getValue() != OPEN_PAREN)
	{
		delete relationNode;
		delete listNode;
		ts.pushToken(t);
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer attributeListNode = parseAttributeList(ts);
	if (attributeListNode->getType() == PARSE_FAILURE )
	{
		delete relationNode;
		delete listNode;
		delete attributeListNode;
		string* value = new string("Failed to parse create");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}
	t = ts.getToken();
	if (t.getValue() != CLOSE_PAREN)
	{
		delete relationNode;
		delete listNode;
		delete attributeListNode;
		string* value = new string("Failed to parse crate");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	string* value = new string(CREATE_TABLE);
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
		string* value = new string("Failed to parse update");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse close");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer atrributeValuePairNode = parseAttributeValuePairNode(ts);
	if ( atrributeValuePairNode->getType() ==  PARSE_FAILURE){

		delete relationName;
		delete atrributeValuePairNode;
		string* value = new string("Failed to parse close");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();

	if (t.getValue() != WHERE){

		delete relationName;
		delete atrributeValuePairNode;
		ts.pushToken(t);
		string* value = new string("Failed to parse close");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

		ConditionTree* tree = parseConditionTree(ts);
		EvalNodePointer conditionNode = new EvalNode(NULL, CONDITION_TREE, (void*)tree);

	if (tree->getRoot()->getType() == PARSE_FAILURE){

		delete relationName;
		delete atrributeValuePairNode;
		delete conditionNode;
		string* value = new string("Failed to parse close");
		result = new EvaluationTree::Node(NULL, PARSE_FAILURE, (void*)value);
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
		string* value = new string("Failed to parse Insert, no Insert");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*) value );
		return result;
	}
	EvalNodePointer relationName = parseRelationName(ts);
	
	if (relationName->getType() == PARSE_FAILURE){
		delete relationName;
		string* value = new string("Failed to parse insert, no relationName");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	t = ts.getToken();
	if (t.getValue() != VALUES_FROM){
		ts.pushToken(t);
	}
	else{
		cout << "A" << endl;
		t = ts.getToken();
		if (t.getValue() != OPEN_PAREN)
		{
			ts.pushToken(t);
			delete relationName;
			string* value = new string("Failed to parse insert, no literalList");
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return result;
		}
		EvalNodePointer literalList = parseLiteralList(ts);
		if (literalList->getType() == PARSE_FAILURE){
			delete relationName;
			delete literalList;
			string* value = new string("Failed to parse insert, no literalList");
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return result;
		}


		t = ts.getToken();

		if (t.getValue() != CLOSE_PAREN)
		{

			ts.pushToken(t);
			delete literalList;
			delete relationName;
			string* value = new string("Failed to parse insert, no literalList");
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
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
			string* value = new string("Failed to parse insert, no expr");
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);

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
	if (t.getValue() != DELETE){

		ts.pushToken(t);
		string* value = new string("Failed to parse delete, no DELETE");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	EvalNodePointer relationName = parseRelationName(ts);
	if (relationName->getType() == PARSE_FAILURE){
		delete relationName;
		string* value = new string("Failed to parse delelte, no relation");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);

		return result;
	}

	t = ts.getToken();
	if (t.getValue() != WHERE){

		ts.pushToken(t);
		delete relationName;
		string* value = new string("Failed to parse delete, no WHERE");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	ConditionTree* tree = parseConditionTree(ts);
	EvalNodePointer conditionNode = new EvalNode(NULL, CONDITION_TREE, (void*)tree);

	if (tree->getRoot()->getType() == PARSE_FAILURE){

		delete relationName;
		delete conditionNode;
		string* value = new string("Failed to parse create, no attibuteList");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
		return result;
	}

	string* value = new string(DELETE);
	result = new EvalNode(NULL, COMMAND_OPERATOR, (void*)value);
	result->addChild(relationName);
	result->addChild(conditionNode);
	return result;

}

EvalNodePointer    parseTypedAttributeList(TokenStream& ts){

	EvalNodePointer result;
	vector< tuple<string , string> >* attributetypelist = new vector< tuple<string , string> >();


	EvalNodePointer node;
	EvalNodePointer type;

	bool keepGoing = true;
	do{

		node = parseAttributeName(ts);
		if ((node->getType() != PARSE_FAILURE))
		{
			type = parseType(ts);

			if ( (type->getType() == PARSE_FAILURE))
			{
				delete node;
				delete type;

				delete attributetypelist;
				string* value = new string("Failure to parse pair when one is expected");
				result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
				return result;
			}
			else
			{
				string* valueAtt = new string((*static_cast<string*>(node->getValue())));
				string* valueType = new string((*static_cast<string*> (type->getValue())));

				attributetypelist->push_back(make_tuple((*valueType), (*valueAtt)));

				delete valueAtt;
				delete valueType;

			}
		}
		else
		{

			//delete node;
			//delete attributetypelist;
			string* value = new string("Failure to parse pair when one is expected");
			result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
			return result;
		}

	

		Token t = ts.getToken();
		if (t.getValue() != COMMA)
		{

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
		string* value = new string("Failed to parse type, no type");
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value);
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
