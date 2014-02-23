#ifndef DBMS_H
#define DBMS_H

#include "Table.h"
#include "Engine.h"
#include "QueryHandler.h"

namespace std{
	class DBMS{

	public:
		DBMS();

		//A query returns a table object to the caller
		Table query(string query);
		//The DBMS will run each string in the commands vector through its parserunit as if a user was 
		//executing each line as a query
		void  load(vector<string> commands);

	private:
	public:
		Engine* engine;
		QueryHandler* qh;

	};

}

#endif DBMS_H