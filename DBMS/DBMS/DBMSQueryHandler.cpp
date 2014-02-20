#include "QueryHandler.h"


#include "TokenStream.h"
QueryHandler::QueryHandler(Engine* e){

	engine = e;
	eval = new Evaluator(e , this);
}


Table* QueryHandler::query(string query){

	try {
		TokenStream ts = (lex(query)); 
		EvaluationTree* tree = parseQuery(ts);
		Table* tablePointer = eval->Evaluate(tree);
		return tablePointer;
	}
	catch (const char* error) {
		cout << error;
		return NULL;
	}
}