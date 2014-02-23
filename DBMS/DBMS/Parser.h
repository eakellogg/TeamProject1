#ifndef PARSER_H
#define PARSER_H


#include "EvaluationTree.h"
#include "ConditionTree.h"



	typedef std::EvaluationTree::Node* EvalNodePointer;
	typedef std::EvaluationTree::Node  EvalNode;
	typedef std::ConditionTree::Node*  CondNodePointer;
	typedef std::ConditionTree::Node   CondNode;

	//Parse a query from the stream
	std::EvaluationTree* parseQuery(TokenStream& ts); 

	//Parse a relationname from the input stream
	EvalNodePointer parseRelationName(TokenStream& ts); 

	//Parse an expression
	EvalNodePointer parseExpresion(TokenStream& ts);  

	//Parse an selection
	EvalNodePointer parseSelection(TokenStream& ts);

	//Parse an projection
	EvalNodePointer parseProjection(TokenStream& ts); 

	//Parse an renaming
	EvalNodePointer parseRenaming(TokenStream& ts); 

	//Parse an Union
	EvalNodePointer parseUnion(TokenStream& ts); 

	//Parse an Difference
	EvalNodePointer parseDifference(TokenStream& ts);

	//Parse an Product
	EvalNodePointer parseProduct(TokenStream& ts); 

	//Parse an NaturalJoin
	EvalNodePointer parseNaturalJoin(TokenStream& ts);  

	//Parse an Atomic-Expr
	EvalNodePointer parseAtomicExpr(TokenStream& ts);  

	//Parse an ConditionTree The root will be a of type failure if failed to parse
	std::ConditionTree*        parseConditionTree(TokenStream& ts); 

	//Parse AttributeList
	EvalNodePointer       parseAttributeList(TokenStream& ts); 

	//Parse Attribute 
	EvalNodePointer       parseAttributeName(TokenStream& ts);  

	//Parse Command
	std::EvaluationTree*    parseCommand(TokenStream& ts); 

	//Parse Open
	EvalNodePointer    parseOpen(TokenStream& ts); 

	//Parse Close
	EvalNodePointer    parseClose(TokenStream& ts);

	//Parse Write
	EvalNodePointer    parseWrite(TokenStream& ts); 

	//Parse Write
	EvalNodePointer    parseExit(TokenStream& ts); 

	//Parse Show
	EvalNodePointer    parseShow(TokenStream& ts); 

	//Parse Create
	EvalNodePointer    parseCreate(TokenStream& ts); 

	//Parse Update
	EvalNodePointer    parseUpdate(TokenStream& ts);

	//Parse Insert
	EvalNodePointer    parseInsert(TokenStream& ts); 

	//Parse Delete
	EvalNodePointer    parseDelete(TokenStream& ts); 

	//Should this fail if no pairs found? Help
	//Parse a typed attribute list
	EvalNodePointer    parseTypedAttributeList(TokenStream& ts); 

	//Parse a Type
	EvalNodePointer    parseType(TokenStream& ts); 

	//Parse an attribute value pair node
	EvalNodePointer    parseAttributeValuePairNode(TokenStream& ts); 

	//Parse a literal list
	EvalNodePointer    parseLiteralList(TokenStream& ts); 

	//Parse Disjunction
	CondNodePointer parseDisjunction(TokenStream& ts);

	//Parse Conjunction
	CondNodePointer parseConjunction(TokenStream& ts); 

	//Parse Comparison
	CondNodePointer parseComparison(TokenStream& ts);

	//Parse Operand
	CondNodePointer parseOperand(TokenStream& ts); 

#endif
