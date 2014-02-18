


#include "DBMS.h"

DBMS::DBMS()
{
		 engine = new Engine(this);
		 qh = new QueryHandler(engine);
}


	 Table DBMS::query(string query){

		 Table* tablePointer = qh->query(query);

		 if (tablePointer != NULL) {
			 return *tablePointer; //Return a copy
		 }
		 else {
			 return Table();
		 }
		 //return Table();
	 }

	 //The DBMS will run each string in the commands vector through its parserunit as if a user was 
	 //executing each line as a query
	 void  DBMS::load(vector<string> commands){
		 for (int i = 0; i < commands.size(); i++)
		 {
			 qh->query(commands[i]);
		 }
	 }