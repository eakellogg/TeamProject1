#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Parser.h"
#include "Engine.h"
#include "QueryHandler.h"

class Engine;
class DBMS;
class QueryHandler;

//Evaluators take in the parsed tree and call the appropriate functions
class Evaluator{

	//holds the query views, maps from name to the table created
	map<string, Table*> views;

	//pointer to engine that it will be calling
	Engine* DBMS;

	//pointer to queryHandler that is using it
	//this is for loading queries from a file
	QueryHandler* queryHandle;

public:
	//constructor
	Evaluator(Engine* dbms, QueryHandler* queryHandle);

	//function for evaluating a tree
	Table* Evaluate(EvaluationTree* tree);
};

#endif