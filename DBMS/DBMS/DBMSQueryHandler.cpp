#include "QueryHandler.h"


#include "TokenStream.h"
QueryHandler::QueryHandler(Engine* e){

	engine = e;
	eval = new Evaluator(e , this);
}


Table* QueryHandler::query(string query){

	cout << "Trying to lex" << endl;
	TokenStream ts = (lex( query)); //Is there a copy constructor?
	cout << "Finished lexing" << endl;
	EvaluationTree* tree = parseQuery(ts);
	cout << "Finished parsing" << endl;
	Table* tablePointer = eval->Evaluate(tree);
	cout << "Finished evaluation" << endl;
	return tablePointer;
}