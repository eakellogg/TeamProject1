#ifndef PARSER_H
#define PARSER_H


#include "EvaluationTree.h"
#include "ConditionTree.h"


typedef EvaluationTree::Node* EvalNodePointer;
typedef EvaluationTree::Node  EvalNode;
typedef ConditionTree::Node*  CondNodePointer;
typedef ConditionTree::Node   CondNode;

//Parse a query from the stream
EvaluationTree* parseQuery(TokenStream& ts); //Done

//Parse a relationname from the input stream
EvalNodePointer parseRelationName(TokenStream& ts); //Done and Tested

//Parse an expression
EvalNodePointer parseExpresion(TokenStream& ts); //Done 

//Parse an selection
EvalNodePointer parseSelection(TokenStream& ts); //Done

//Parse an projection
EvalNodePointer parseProjection(TokenStream& ts);  //Done

//Parse an renaming
EvalNodePointer parseRenaming(TokenStream& ts); //Done

//Parse an Union
EvalNodePointer parseUnion(TokenStream& ts);  //Done

//Parse an Difference
EvalNodePointer parseDifference(TokenStream& ts); //Done

//Parse an Product
EvalNodePointer parseProduct(TokenStream& ts); //Done

//Parse an NaturalJoin
EvalNodePointer parseNaturalJoin(TokenStream& ts);  //Done

//Parse an Atomic-Expr
EvalNodePointer parseAtomicExpr(TokenStream& ts);  //Done

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
CondNodePointer parseDisjunction(TokenStream& ts); //Done and Tested

//Parse Conjunction
CondNodePointer parseConjunction(TokenStream& ts); //Done and Tested

//Parse Comparison
CondNodePointer parseComparison(TokenStream& ts); //Done and Tested

//Parse Operand
CondNodePointer parseOperand(TokenStream& ts); //Done and Tested

#endif
