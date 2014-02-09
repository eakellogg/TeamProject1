#pragma once

#include "Engine.h"
#include <algorithm>


/*********************************************************************************
helper functions
*********************************************************************************/


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


// verify that the data of both rows match in all necessary columns that are shared
static bool checkMatchingData(Table* firstTable, Table* secondTable, vector<string> sharedColumns) {
	// compare the current rows of both tables
	for (int i = 0; i < sharedColumns.size(); i++) {
		// if the data of the current rows don't match on a particular column
		if (firstTable->getVariable(sharedColumns[i])->getValue() != secondTable->getVariable(sharedColumns[i])->getValue()) {
			return false;
		}
	}
	return true; // the current rows matched on every shared column
}


// make and return a new row with the naturally joined information
static vector<Attribute*> fillNewRow(Table* firstTable, Table* secondTable, vector<string> newColumnTitles, int identifierCount) {
	vector<Attribute*> newRow;

	// get all needed data from first table
	for (int i = 0; i < firstTable->getColumnTitles().size(); i++) {
		newRow.push_back(firstTable->getVariable(newColumnTitles[i]));
	}
	// get all needed data from second table
	for (int j = firstTable->getColumnTitles().size(); j < newColumnTitles.size() - 1; j++) {
		newRow.push_back(secondTable->getVariable(newColumnTitles[j]));
	}

	Attribute* identifier = new Attribute("int", to_string(identifierCount));
	newRow.push_back(identifier);

	return newRow;
}


/*********************************************************************************
natural join
*********************************************************************************/


// calculates the natural join of the two given tables and returns a new table with the result
Table* Engine::naturalJoin(Table* firstTable, Table* secondTable) {
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
		// check to make sure that the column we add is not in the shared column already added
		if (find(sharedColumns.begin(), sharedColumns.end(), secondTableColumns[j]) == sharedColumns.end()) {
			newColumnTitles.push_back(secondTableColumns[j]);
			newColumnTypes.push_back(secondTable->getTypeOfColumn(secondTableColumns[j]));
		}
	}
	
	string newKey = firstTable->getTableName() + secondTable->getTableName();
	newColumnTitles.push_back(newKey);
	newColumnTypes.push_back("int");

	// new table to add data to
	Table* newTable = new Table("New Table", newKey, newColumnTypes, newColumnTitles);
	
	int firstTableOffset = 0;
	int secondTableOffset = 0;
	int identifierCount = 0;
	map<string, vector<Attribute*>> firstTableData = firstTable->getData();
	map<string, vector<Attribute*>> secondTableData = secondTable->getData();
	
	// iterate through all rows of the first table
	for (map<string, vector<Attribute*>>::iterator i = firstTableData.begin(); i != firstTableData.end(); i++) {
		firstTable->setCurrentRow(firstTableOffset); // set current row of first table to correct row
		
		// for each rows of first table, iterate through all rows of the second table
		for (map<string, vector<Attribute*>>::iterator j = secondTableData.begin(); j != secondTableData.end(); j++) {
			secondTable->setCurrentRow(secondTableOffset); // set current row of second table to correct row

			// make sure the current rows match on every shared column
			if (checkMatchingData(firstTable, secondTable, sharedColumns)) {
				vector<Attribute*> newRow = fillNewRow(firstTable, secondTable, newColumnTitles, identifierCount);
				identifierCount++;
				newTable->addRow(newRow, newColumnTypes);
			}
			secondTableOffset++;
		}	
		secondTableOffset = 0;
		firstTableOffset++;
	}
	
	return newTable;
}