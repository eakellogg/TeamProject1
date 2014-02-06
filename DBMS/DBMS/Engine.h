#pragma once

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>

#include "Table.h"

using namespace std;


class Engine {
	vector<Table*> tables;

public:
/*********************************************************************************
	constructor
*********************************************************************************/


	//constructor
	Engine()
	{	}


/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	//we can remove this section if we find we don't need it
	vector<Table*> getTables() { return tables; }


/*********************************************************************************
	modifying functions
*********************************************************************************/

	// create a table with the row types and column titles given
	void createTable(string tableName, vector<string> rowTypes, vector<string> columnTitles) {
		tables.push_back(new Table(tableName, rowTypes, columnTitles));
	}


	// delete a table from the database
	void dropTable(string tableName) {
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
	void insertInto(string tableName, vector<string> row, vector<string> rowTypes) {
		Table* tempTable = findTable(tableName);
		tempTable->addRow(row, rowTypes);
	}


	// update a row in the table with the proper name
	void update(string tableName, vector<string> row, vector<string> rowTypes) {
		int pos = 0; //!!!!!!!!!!!!!! REALLY NEED TO FIND THIS METHOD
		Table* tempTable = findTable(tableName);
		tempTable->updateRow(row, rowTypes, pos);		
	}


	// delete a row in the table with the proper name
	void deleteFrom(string tableName, int pos) {
		Table* tempTable = findTable(tableName);
		tempTable->deleteRow(pos);
	}


/*********************************************************************************
	helper functions
*********************************************************************************/


	// search database for a table with matching name
	Table* findTable(string tableName) {
		// compare passed name to names of all tables in the database
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i]->getTableName() == tableName) {
				return tables[i];
			}
		}
		throw "table does not exist"; // throwing exception prevents needing checks for unfound tables in other functions
	}
};
