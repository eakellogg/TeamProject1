#pragma once

#include "Engine.h"

using namespace std;

	/*********************************************************************************
	constructor
	*********************************************************************************/


	//constructor
	Engine::Engine()
	{	}


	/*********************************************************************************
	non-modifying functions / accessor methods
	*********************************************************************************/


	//we can remove this section if we find we don't need it
	vector<Table*> Engine::getTables() { return tables; }


	/*********************************************************************************
	modifying functions
	*********************************************************************************/

	// create a table with the row types and column titles given
	void Engine::createTable(string tableName, string keyName, vector<string> columnTypes, vector<string> columnTitles) {
		if (find(columnTitles.begin(), columnTitles.end(), keyName) == columnTitles.end()) {
			throw "key name does not match any column, table not created";
		}
		tables.push_back(new Table(tableName, keyName, columnTypes, columnTitles));
	}


	// delete a table from the database
	void Engine::dropTable(string tableName) {
		// search database for a table with matching name; delete table if it exists
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i]->getTableName() == tableName) {
				tables.erase(tables.begin() + i); // must use tables.begin() to get iterator; increment with i
				return;
			}
		}
		throw "table does not exist";
	}


	// insert a row into the table with the proper name
	void Engine::insertInto(string tableName, vector<Attribute*> row, vector<string> columnTypes) {
		Table* tempTable = findTable(tableName);
		tempTable->addRow(row, columnTypes);
	}


	// changes multiple rows and multiple Attributes at a time
	// update a row in the table with the proper name
	//pair <name, literal>
	// not done yet
	/*	void update(string tableName, vector<string> conditions, vector<string> columnNames) {
	int pos = 0; //!!!!!!!!!!!!!! REALLY NEED TO FIND THIS METHOD
	Table* tempTable = findTable(tableName);
	tempTable->updateRow(row, rowTypes, pos);
	}
	*/

	// delete a row in the table with the proper name
	//same condition problem as update
	/*
	void deleteFrom(string tableName, int pos) {
	Table* tempTable = findTable(tableName);
	tempTable->deleteRow(pos);
	}
	*/

	// calculates the union of the two given tables and returns a new table with the result
	//Table* Engine::setUnion(Table* first, Table* secondTable); // see setUnion.cpp

	// calculates the difference of the two given tables and returns a new table with the result
	//Table* Engine::setDifference(Table* first, Table* secondTable); // see setDifference.cpp

	// calculates the natural join of the two given tables and returns a new table with the result
	//Table* Engine::naturalJoin(Table* first, Table* secondTable); // see NaturalJoin.cpp

	// calculates the cross product of the two given tables and returns a new table with the result
	//Table* Engine::crossProduct(Table* first, Table* secondTable); // see CrossProduct.cpp


	/*********************************************************************************
	helper functions
	*********************************************************************************/
	// search database for a table with matching name
	Table* Engine::findTable(string tableName) {
		// compare passed name to names of all tables in the database
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i]->getTableName() == tableName) {
				return tables[i];
			}
		}
		throw "table does not exist"; // throwing exception prevents needing checks for unfound tables in other functions
	}
