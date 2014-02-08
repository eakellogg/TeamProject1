#pragma once

#include "Engine.h"


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


/*********************************************************************************
natural join
*********************************************************************************/


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