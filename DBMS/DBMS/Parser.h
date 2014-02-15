
#ifndef PARSER_H
#define PARSER_H


#include "EvaluationTree.h"
#include "TokenStream.h"
#include "ConditionTree.h"
#include "TokenStream.h"

typedef EvaluationTree::Node* EvalNodePointer;
typedef EvaluationTree::Node  EvalNode;
typedef ConditionTree::Node*  CondNodePointer;
typedef ConditionTree::Node   CondNode;

//Parse a query from the stream
EvaluationTree* parseQuery(TokenStream& ts); //Done

//Parse a relationname from the input stream
EvaluationTree::Node* parseRelationName(TokenStream& ts); //Done and Tested

//Parse an expression
EvaluationTree::Node* parseExpresion(TokenStream& ts); //Done 

//Parse an selection
EvaluationTree::Node* parseSelection(TokenStream& ts); //Done

//Parse an projection
EvaluationTree::Node* parseProjection(TokenStream& ts);  //Done

//Parse an renaming
EvaluationTree::Node* parseRenaming(TokenStream& ts); //Done

//Parse an Union
EvaluationTree::Node* parseUnion(TokenStream& ts);  //Done

//Parse an Difference
EvaluationTree::Node* parseDifference(TokenStream& ts); //Done

//Parse an Product
EvaluationTree::Node* parseProduct(TokenStream& ts); //Done

//Parse an NaturalJoin
EvaluationTree::Node* parseNaturalJoin(TokenStream& ts);  //Done

//Parse an Atomic-Expr
EvaluationTree::Node* parseAtomicExpr(TokenStream& ts);  //Done

//Parse an ConditionTree The root will be a of type failure if failed to parse
ConditionTree*        parseConditionTree(TokenStream& ts); //Done and Tested

//Parsse AttributeList
EvalNodePointer       parseAttributeList(TokenStream& ts); //Done and Tested

//Parse Attribute 
EvalNodePointer       parseAttributeName(TokenStream& ts); //Done 

EvaluationTree*    parseCommand(TokenStream& ts); //Done and Tested

EvalNodePointer    parseOpen(TokenStream& ts); //Done and Tested 

EvalNodePointer    parseClose(TokenStream& ts); //Done and Tested

EvalNodePointer    parseWrite(TokenStream& ts); //Done and Tested

EvalNodePointer    parseExit(TokenStream& ts); //Done and Tested

EvalNodePointer    parseShow(TokenStream& ts); //Done waiting for atomic expr

EvalNodePointer    parseCreate(TokenStream& ts); //Done and Tested

EvalNodePointer    parseUpdate(TokenStream& ts);//Done and Tested

EvalNodePointer    parseInsert(TokenStream& ts); //Done almost all tested

EvalNodePointer    parseDelete(TokenStream& ts); //Done and Tested


//Should this fail if no pairs found? Help
EvalNodePointer    parseTypedAttributeList(TokenStream& ts); //Done and Tested

EvalNodePointer    parseType(TokenStream& ts); //Done  and Tested

EvalNodePointer    parseAttributeValuePairNode(TokenStream& ts); //Done and Tested 

EvalNodePointer    parseLiteralList(TokenStream& ts); //Done and Tested


ConditionTree::Node* parseDisjunction(TokenStream& ts); //Done and Tested

ConditionTree::Node* parseConjunction(TokenStream& ts); //Done and Tested

ConditionTree::Node* parseComparison(TokenStream& ts); //Done and Tested

ConditionTree::Node* parseOperand(TokenStream& ts); //Done and Tested


#endif