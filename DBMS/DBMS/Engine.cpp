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
		for (unsigned int i = 0; i < tables.size(); i++) {
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


/*********************************************************************************
	helper functions
*********************************************************************************/


	// search database for a table with matching name
	Table* Engine::findTable(string tableName) {
		// compare passed name to names of all tables in the database
		for (unsigned int i = 0; i < tables.size(); i++) {
			if (tables[i]->getTableName() == tableName) {
				return tables[i];
			}
		}
		throw "table does not exist"; // throwing exception prevents needing checks for unfound tables in other functions
	}
