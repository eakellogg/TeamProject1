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

//Parse AttributeList
EvalNodePointer       parseAttributeList(TokenStream& ts); //Done and Tested

//Parse Attribute 
EvalNodePointer       parseAttributeName(TokenStream& ts); //Done 

//Parse Command
EvaluationTree*    parseCommand(TokenStream& ts); //Done and Tested

//Parse Open
EvalNodePointer    parseOpen(TokenStream& ts); //Done and Tested 

//Parse Close
EvalNodePointer    parseClose(TokenStream& ts); //Done and Tested

//Parse Write
EvalNodePointer    parseWrite(TokenStream& ts); //Done and Tested

//Parse Write
EvalNodePointer    parseExit(TokenStream& ts); //Done and Tested

//Parse Show
EvalNodePointer    parseShow(TokenStream& ts); //Done waiting for atomic expr

//Parse Create
EvalNodePointer    parseCreate(TokenStream& ts); //Done and Tested

//Parse Update
EvalNodePointer    parseUpdate(TokenStream& ts);//Done and Tested

//Parse Insert
EvalNodePointer    parseInsert(TokenStream& ts); //Done almost all tested

//Parse Delete
EvalNodePointer    parseDelete(TokenStream& ts); //Done and Tested

//Should this fail if no pairs found? Help
//Parse a typed attribute list
EvalNodePointer    parseTypedAttributeList(TokenStream& ts); //Done and Tested

//Parse a Type
EvalNodePointer    parseType(TokenStream& ts); //Done  and Tested

//Parse an attribute value pair node
EvalNodePointer    parseAttributeValuePairNode(TokenStream& ts); //Done and Tested 

//Parse a literal list
EvalNodePointer    parseLiteralList(TokenStream& ts); //Done and Tested

//Parse Disjunction
ConditionTree::Node* parseDisjunction(TokenStream& ts); //Done and Tested

//Parse Conjunction
ConditionTree::Node* parseConjunction(TokenStream& ts); //Done and Tested

//Parse Comparison
ConditionTree::Node* parseComparison(TokenStream& ts); //Done and Tested

//Parse Operand
ConditionTree::Node* parseOperand(TokenStream& ts); //Done and Tested

#endif
