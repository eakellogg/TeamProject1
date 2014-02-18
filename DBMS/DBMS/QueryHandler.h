
#include "DBMS.h"
#include "Engine.h"

#ifndef QH_H
#define QH_H

class Engine;

class QueryHandler{

public:

	QueryHandler(Engine* e);

	//This will return a pointer to the table the query creates
	Table* query(string query);

private:
	Engine* engine; //A pointer to the engine who will do all the table manipulation

};

#endif