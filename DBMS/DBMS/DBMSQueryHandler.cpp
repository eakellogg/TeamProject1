#include "QueryHandler.h"


#include "TokenStream.h"
QueryHandler::QueryHandler(Engine* e){

	engine = e;
	eval = new Evaluator(e , this);
}


Table* QueryHandler::query(string query){


	TokenStream ts = (lex( query)); //Is there a copy constructor?

	EvaluationTree* tree = parseQuery(ts);

	Table* tablePointer = eval->Evaluate(tree);

	return tablePointer;
}