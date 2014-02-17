#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Parser.h"
#include "Engine.h"

class Evaluator{
	map<string, Table*> views;
	Engine* DBMS;

public:
	Evaluator(Engine* dbms);
	Table* Evaluate(EvaluationTree* tree);
};

#endif