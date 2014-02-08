#pragma once

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>

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
	void insertInto(string tableName, string key, vector<Attribute*> row, vector<string> columnTypes) {
		Table* tempTable = findTable(tableName);
		tempTable->addRow(key, row, columnTypes);
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


	// calculates the natural join of the two given tables and returns a new table with the result
	//Table* naturalJoin(Table* a, Table* b); // see NaturalJoin.cpp


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











/*
If you uncomment this and run the natrual join test case, thing won't be problimatic. See natural join .cpp file for the exact same code.



	// ensure there is a common column between two tables to enable natural join
	static vector<string> getCommonColumn(Table* firstTable, Table* secondTable) {
		vector<string> firstTableColumns = firstTable->getColumnTitles();
		vector<string> secondTableColumns = secondTable->getColumnTitles();
		vector<string> sharedColumns;

		for (int i = 0; i < firstTableColumns.size(); i++) { // iterate through all of first table columns
			for (int j = 0; j < secondTableColumns.size(); j++) { // iterate through all of second table columns
				if (firstTableColumns[i] == secondTableColumns[j]) { // if match is found between names, check type
					if (firstTable->getColumnTypes()[i] == secondTable->getColumnTypes()[j]) { // if name and type match, the tables can be naturally joined
						sharedColumns.push_back(firstTableColumns[i]);
					}
				}
			}
		}
		return sharedColumns;
	}


	/*********************************************************************************
	natural join
	*********************************************************************************/

/*
	// calculates the natural join of the two given tables and returns a new table with the result
	Table* naturalJoin(Table* firstTable, Table* secondTable) {
		vector<string> firstTableColumns = firstTable->getColumnTitles();
		vector<string> secondTableColumns = secondTable->getColumnTitles();
		vector<string> sharedColumns = getCommonColumn(firstTable, secondTable);
		// check first to see if columns can be natrually joined
		if (sharedColumns.size() == 0) {
			throw "tables cannot be naturally joined due to no common column";
		}

		vector<string> newColumnTitles;
		vector<string> newColumnTypes;
		// add all of first table's column names/types to the new table's column names/types
		for (int i = 0; i < firstTableColumns.size(); i++) {
			newColumnTitles.push_back(firstTableColumns[i]);
			newColumnTypes.push_back(firstTable->getTypeOfColumn(firstTableColumns[i]));
		}

		// add all of second table's column names/types to the new table's column names/types if they didn't exist in the first table
		for (int j = 0; j < secondTableColumns.size(); j++) {
			// check to make sure that the column we add was not already added from the first table
			// this assumes that two columns having the same name means they are equivalent (assumes equal names have equal types)
			if (find(firstTableColumns.begin(), firstTableColumns.end(), secondTableColumns[j]) == firstTableColumns.end()) {
				newColumnTitles.push_back(secondTableColumns[j]);
				newColumnTypes.push_back(secondTable->getTypeOfColumn(secondTableColumns[j]));
			}
		}

		Table* newTable = new Table("New Table", newColumnTypes, newColumnTitles);
		return newTable;
	}



*/







};
