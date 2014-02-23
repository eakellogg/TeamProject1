#include "FAKE_DBMS.h"


#include "TokenStream.h"
#include "Lexer.h"
#include "Constants.h"
#include <sstream>
/*
This class wraps the DBMS provide by another group into a neat litle package that
endeavers to behave just like our own DBMS
*/
using namespace std;

	//Attribtue type of fake table
	typedef FAKE_DBMS::Datum fake_att;
	
	//This converts FAKE_DBMS tables into DBMS tables
	Table convertTable(FAKE_DBMS::Table t , string name);

		//This emualates DBMS::query(string query)
	Table Fake_DBMS::query(string query){
		

		connection.executeCommand(query);

		TokenStream ts  = lex(query);

		Token t = ts.getToken();

		Table realTable;
		if (t.getType() == IDENTIFIER )
		{
			FAKE_DBMS::Table fooTable = connection.getTempTable( t.getValue() );
			realTable = convertTable(fooTable, t.getValue());

		}
	
		return realTable;

	}


	Table convertTable(FAKE_DBMS::Table t , string name){

		string tableName = name;
		vector<string> keyNames = t.keyNames;

		vector < vector< fake_att > > oldData = t.data;

		vector< string> columnTitles = t.attributeNames;

		vector< string > columTypes;

		unsigned int numRows = oldData.size();

		//Find the types of the columns using the first row of the old table
		for (unsigned int i = 0; i < numRows; i++) 
		{
			fake_att entry = oldData[0][i];
			if (entry.numData = -999) //Their key for it being a string type
			{
				columTypes.push_back(STRING_LITERAL);

			}
			else
				columTypes.push_back(INT_LITERAL);
		}
		
		Table newTable(tableName, keyNames, columTypes, columnTitles);


		unsigned int numColumns = oldData[0].size();
		for (unsigned int i = 0; i < numRows; i++) //For every row
		{

			vector< Attribute* > newRow; //The new row to be added
			
			for (unsigned int j = 0; j < numColumns; j++)
			{
				fake_att oldEntry = oldData[i][j];

				Attribute* newEntry = NULL;
				if (oldEntry.numData == -999)
				{
					newEntry = new Attribute(STRING_LITERAL, oldEntry.stringData);
				}
				else
				{
					int numVal = oldEntry.numData; 
					string strVal;      
					ostringstream convert; 
					convert << numVal;      
					strVal = convert.str(); 
					newEntry = new Attribute(INT_LITERAL, strVal);
				}
				newRow.push_back(newEntry);
			}

			newTable.addRow(newRow, columTypes);

		}
		

		return newTable;
	}
