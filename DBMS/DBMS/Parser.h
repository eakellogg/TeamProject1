



#include "EvaluationTree.h"
#include "TokenStream.h"
#include "ConditionTree.h"

typedef EvaluationTree::Node* EvalNodePointer;
typedef EvaluationTree::Node  EvalNode;
typedef ConditionTree::Node*  CondNodePointer;
typedef ConditionTree::Node   CondNode;

//Parse a query from the stream
EvaluationTree* parseQuery(TokenStream& ts); //Done

//Parse a relationname from the input stream
EvaluationTree::Node* parseRelationName(TokenStream& ts); //Done

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
ConditionTree*        parseConditionTree(TokenStream& ts); //THINK

//Parsse AttributeList
EvalNodePointer           parseAttributeList(TokenStream& ts); //Done

//Parse Attribute 
EvalNodePointer           parseAttributeName(TokenStream& ts); //Done

EvaluationTree*    parseCommand(TokenStream& ts); //Done

EvalNodePointer    parseOpen(TokenStream& ts);

EvalNodePointer    parseClose(TokenStream& ts);

EvalNodePointer    parseWrite(TokenStream& ts);

EvalNodePointer    parseExit(TokenStream& ts);

EvalNodePointer    parseShow(TokenStream& ts);

EvalNodePointer    parseCreate(TokenStream& ts);

EvalNodePointer    parseUpdate(TokenStream& ts);

EvalNodePointer    parseInsert(TokenStream& ts);

EvalNodePointer    parseDelete(TokenStream& ts);

EvalNodePointer    parseTypedAttributeList(TokenStream& ts);

EvalNodePointer    parseType(TokenStream& ts);

