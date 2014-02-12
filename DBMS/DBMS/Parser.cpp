#include "Parser.h"

#include <list>

EvaluationTree* parseQuery(TokenStream& ts){

	EvaluationTree::Node* leftChild = parseRelationName(ts);

	if (leftChild->getType() != RELATION_NAME)
	{
		//TODO 
		//THROW ERROR
	}

	string parentType = QUERY_OPERATOR;
	
	Token token = ts.getToken();
	if (token.getType()!= PLACEMENT_SYMBOL )
	{
		//TODO
		//I'm not great with exceptions I need ideas
		//throw error;
	}
	
	string* value = new string(token.getValue());
	EvaluationTree::Node* root = new EvaluationTree::Node(NULL, QUERY_OPERATOR, (void*) value);
	
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

EvaluationTree::Node* parseRelationName(TokenStream& ts){

	EvaluationTree::Node* result;

	Token t = ts.getToken();
	if (t.getType() == IDENTIFIER){
		
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
	if (condtree->getRoot()->getType() == FAILURE){
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

EvalNodePointer pareseProjection(TokenStream& ts){

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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue != UNION){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse union, no UNION symbole"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue != DIFFERENCE){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse difference, no DIFFERENCE symbol"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE ){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value) );
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue != PRODUCT){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse PRODUCT, no PRODUCT symbol"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value) );
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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value));
		return result;
	}

	Token t = ts.getToken();
	if (t.getValue != JOIN){
		ts.pushToken(t);
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)("Couldn't parse natural join, no join symbol"));
		return result;
	}

	EvalNodePointer rightChild = parseAtomicExpr(ts);
	if (rightChild->getType() == PARSE_FAILURE){

		string* value = new string((*static_cast<string*>((rightChild->getValue()))));
		delete leftChild;
		delete rightChild;
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value) );
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

	EvalNodePointer result;

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
		result = new EvalNode(NULL, PARSE_FAILURE, (void*)value) );
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
	

ConditionTree*        parseConditionTree(TokenStream& ts){

	ConditionTree* tree = new ConditionTree("", "");
	//parseConjunction(ts , NULL);


}


EvalNodePointer           parseAttributeList(TokenStream& ts){

	EvalNodePointer result;
	list<string*>* attributelist = new list<string*>();


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