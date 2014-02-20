#include "FAKE_DBMS.h"


#include "TokenStream.h"
#include "Lexer.h"

/*
This class wraps the DBMS provide by another group into a neat litle package that
endeavers to behave just like our own DBMS
*/
using namespace std;

		//This emualates DBMS::query(string query)
	Table FAKE_DBMS::query(string query){
		
		connection.exectue(query);

		TokenStream ts = lex(query);

		Token t = ts.getToken();

		Table realTable
		if (t.getType() == IDENTIFER )
		{
			FAKE_DBMS::Table fooTable = connection.getTempTable();
			 //realTable = convertTable( fooTable );

		}
		else
		{
		
		}

		return table;

	}

	/*
	//used to execute a command on the database from within a user application
	void executeCommand(std::string command);

	//get a table from the parser temp table vector
	Table getTempTable(const std::string& tableName);*/

