#pragma once

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include "ConditionTree.h"
#include "Table.h"
#include "Attribute.h"

using namespace std;


class Engine {
	vector<Table*> tables;

public:
	/*********************************************************************************
		constructor
		*********************************************************************************/

	//constructor
	Engine();

	/*********************************************************************************
		non-modifying functions / accessor methods
		*********************************************************************************/

	//we can remove this section if we find we don't need it
	vector<Table*> getTables();

	/*********************************************************************************
		modifying functions
		*********************************************************************************/

	// create a table with the row types and column titles given
	void createTable(string tableName, string keyName, vector<string> columnTypes, vector<string> columnTitles);


	// delete a table from the database
	void dropTable(string tableName);


	// insert a row into the table with the proper name
	void insertInto(string tableName, vector<Attribute*> row, vector<string> columnTypes);

	//Delete all rows in the table that meet the condition
	void deleteFrom(string tableName, ConditionTree t);

	//Change the variables listed to their new values, if the row in the table meets the condition
	void  update(string tableName, vector< tuple<string, string> > namevarpairs, ConditionTree t);

	//Return a table that has only the rows from the old table that meet the condition
	Table* selection(string tableName, ConditionTree t);

	//Return a table that has only the specified columns of the old table
	Table* projection(string startTable, vector<string> variables);

	// calculates the union of the two given tables and returns a new table with the result
	Table* setUnion(Table* first, Table* secondTable); // see setUnion.cpp

	// calculates the difference of the two given tables and returns a new table with the result
	Table* setDifference(Table* first, Table* secondTable); // see setDifference.cpp

	// calculates the natural join of the two given tables and returns a new table with the result
	Table* naturalJoin(Table* first, Table* secondTable); // see NaturalJoin.cpp

	// calculates the cross product of the two given tables and returns a new table with the result
	Table* crossProduct(Table* first, Table* secondTable); // see CrossProduct.cpp


	/*********************************************************************************
		helper functions
		*********************************************************************************/

	// search database for a table with matching name
	Table* findTable(string tableName);
};
