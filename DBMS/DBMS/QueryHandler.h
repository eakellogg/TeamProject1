
#include "DBMS.h"
#include "Engine.h"
#include "lexer.h"
#include "EvaluationTree.h"
#include "Evaluator.h"
#ifndef QH_H
#define QH_H

namespace std{

	class Engine;
	class Evaluator;

	class QueryHandler{

	public:

		QueryHandler(Engine* e);

		//This will return a pointer to the table the query creates
		Table* query(string query);

	private:
		Engine* engine; //A pointer to the engine who will do all the table manipulation
		Evaluator* eval;
	};
}

#endif