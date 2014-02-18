#include "QueryHandler.h"


#include "TokenStream.h"


QueryHandler::QueryHandler(Engine* e){

	engine = e;

}


Table* QueryHandler::query(string query){

	/* WAITING ON LEXER AND EVALU TO un commnet out
	this is api!!!!!!!!!!!!!!!!!!!!!!!!

		TokenStream ts = Lexer.lex( query );
		EvaluationTree* tree = parserQuery(ts);

		Table* tablePointer = Evaluator.eval( engine , tree );

		return tablePointer
	*/
	//Just to compile
	return NULL;
}
