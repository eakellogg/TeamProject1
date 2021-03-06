#pragma once

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include "ConditionTree.h"
#include "Table.h"
#include "Attribute.h"
#include "DBMS.h"

#ifndef ENGINE_H
#define ENGINE_H

namespace std{

class DBMS;

class Engine {
	vector<Table*> tables;

	DBMS* master; //A pointer to the DBMS containing this engine

public:
	/*********************************************************************************
		constructor
	*********************************************************************************/

	//constructor
	Engine( DBMS* master );

	/*********************************************************************************
		non-modifying functions / accessor methods
	*********************************************************************************/

	//we can remove this section if we find we don't need it
	vector<Table*> getTables();

	/*********************************************************************************
		modifying functions
	*********************************************************************************/

	// create a table with the row types and column titles given
	void createTable(string tableName, vector<string> keyName, vector<string> columnTypes, vector<string> columnTitles);

	// delete a table from the database
	void dropTable(Table* table);

	// insert a row into the table with the proper name
	void insertInto(Table* table, vector<Attribute*> row, vector<string> columnTypes);

	// insert a table into another table
	void insertInto(Table* tablea, Table* tableb);

	// change the variables listed to their new values, if the row in the table meets the condition
	void update(Table* table, vector< tuple<string, string> > namevarpairs, ConditionTree t);

	// delete all rows in the table that meet the condition
	void deleteFrom(Table* table, ConditionTree t);

	// return a table that has only the rows from the old table that meet the condition
	Table* selection(Table* oldTable, ConditionTree t);

	// return a table that has only the specified columns of the old table
	Table* projection(Table* oldTable, vector<string> variables);

	// rename the columns in a given table using the given names
	Table* rename(Table* oldTable, vector<string> attributes);

	// calculates the union of the two given tables and returns a new table with the result
	Table* setUnion(Table* first, Table* secondTable); // see setUnion.cpp

	// calculates the difference of the two given tables and returns a new table with the result
	Table* setDifference(Table* first, Table* secondTable); // see setDifference.cpp

	// calculates the natural join of the two given tables and returns a new table with the result
	Table* naturalJoin(Table* first, Table* secondTable); // see NaturalJoin.cpp

	// calculates the cross product of the two given tables and returns a new table with the result
	Table* crossProduct(Table* first, Table* secondTable); // see CrossProduct.cpp

	// opens the file represented by tableName; reads the table into the database
	void openFile(string tableName);

	// closes an open file, saving all changes that occured since opening; removes the table from the database
	void closeFile(Table* table);

	// writes a new file for a table, overwritting an already existing file with the same name if there is one
	void writeFile(Table* table);

	// show a relation by printing the table representing it
	void show(Table* table);

	/*********************************************************************************
		helper functions
	*********************************************************************************/


	// search database for a table with matching name
	Table* findTable(string tableName);
};

}

#endif
