#include "QueryHandler.h"


#include "TokenStream.h"
QueryHandler::QueryHandler(Engine* e){

	engine = e;
	eval = new Evaluator(e , this);
}


Table* QueryHandler::query(string query){

	try {
		TokenStream ts = (lex(query)); //Is there a copy constructor?
		cout << "lexed" << endl;
		EvaluationTree* tree = parseQuery(ts);
		cout << "parsed" << endl;
		Table* tablePointer = eval->Evaluate(tree);
		cout << "evaled" << endl;
		return tablePointer;
	}
	catch (const char* error) {
		cout << error;
		return NULL;
	}
}