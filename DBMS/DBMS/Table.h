#pragma once

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include <map>
#include <iomanip>

#include "Attribute.h"

using namespace std;


class Table {
	string tableName;
	string keyName;
	map< string, vector<Attribute*> > data; // the rows of the table
	vector<string> columnTypes;
	vector<string> columnTitles;
	vector<Attribute*> currentRow;
public:
/*********************************************************************************
	constructor
*********************************************************************************/


	Table(string tableName, string keyName, vector<string> columnTypes, vector<string> columnTitles)
		:tableName(tableName), keyName(keyName), columnTypes(columnTypes), columnTitles(columnTitles)
	{	}


/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	string getTableName() { return tableName; }

	string getKeyName() { return keyName; }

	map< string, vector<Attribute*> > getData() { return data; }

	vector<string> getColumnTypes() { return columnTypes; }

	vector<string> getColumnTitles() { return columnTitles; }

	vector<Attribute*> getCurrentRow() { return currentRow; }


/*********************************************************************************
	modifying functions
*********************************************************************************/


	// add a row to the table
	void addRow(vector<Attribute*> row, vector<string> rowTypes) {
		if (checkMatchingTypes(rowTypes)) {
			currentRow = row;
			string key = getVariable(keyName)->getValue();
			data.insert(make_pair(key, row));
			return;
		}
		throw "types do not match";
	}

/*
	// update an already existing row
	void updateRow(vector<string> newRow, vector<string> rowTypes, int pos) { // need diff. than pos
		if (checkMatchingTypes(rowTypes)) {
			data[pos] = newRow;
			return;
		}
		throw "types do not match";
	}
*/

	// delete a row from the table
	void deleteRow(string key) {
		try {
			data.erase(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}
	}


	// find and return a specific row in the table
	vector<Attribute*> getRow(string key) {
		try {
			return data.at(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}
	}


	// find and return a specific item in a specific row in the table
	Attribute* getItem(string key, string columnName) {
		try {
			currentRow = data.at(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}

		// search the temporary row for correct item based on column name
		for (int i = 0; i < (columnTitles.size() - 1); i++) {
			if (columnTitles[i] == columnName) {
				return currentRow[i];
			}
		}
		throw "column does not exist";
	}


	// takes in a column name, searches the current row, and returns the value of the column name
	Attribute* getVariable(string columnName) {
		for (int i = 0; i < columnTitles.size(); i++) {
			if (columnTitles[i] == columnName) {
				return currentRow[i];
			}
		}
		throw "variable does not exist";
	}


/*********************************************************************************
	helper functions
*********************************************************************************/

	
	// reset the currentRow pointer to the beginning of the map
	void resetCurrentRow() {
		currentRow = data.begin()->second;
	}


	// set the currentRow pointer appropriately with regards to the offset passed
	void setCurrentRow(int offset) {
		auto iterator = data.begin();
		advance(iterator, offset);
		currentRow = (iterator)->second;
	}


	// check to make sure the types of the table's rows and the passed types are equivalent
	bool checkMatchingTypes(vector<string> rowTypes) {
		// check every type of the row in question and compare with table's row types
		for (int i = 0; i < columnTypes.size(); i++) {
			if (rowTypes[i] != columnTypes[i]) {
				return false; // incorrect type was found in the process of adding
			}
		}
		return true;
	}


	// return the type associated with a column name
	string getTypeOfColumn(string columnName) {
		// search all columns in the table by name
		for (int i = 0; i < columnTitles.size(); i++) {
			if (columnTitles[i] == columnName) { // if a match is found, return the corresponding type
				return columnTypes[i];
			}
		}
		throw "column does not exist";
	}


	// print the table in an orderly format
	void printTable() {
		cout << tableName << endl;
	
		// print the column names
		cout << "********************************************************************************************" << endl;
		for (int i = 0; i < columnTitles.size(); i++) {
			cout << left << setw(20) << formatString(columnTitles[i], 20);
		}
		cout << endl << "********************************************************************************************" << endl;
		auto iterator = data.begin();
		// print the data for each row, alligned with the appropriate column
		for (int i = 0; i < data.size(); i++) {
			currentRow = iterator->second;
			// print every individual row's data,alligned with the appropriate column
			for (int j = 0; j < currentRow.size(); j++) {
				cout << left << setw(20) << formatString(currentRow[j]->getValue(), 20);
			}
			cout << endl;
			iterator++;
		}
		cout << endl;
	}


	// limit string's length to the specified limit for proper formatting
	string formatString(string tempName, int limit) {
		if (tempName.length() > limit) {
			tempName = tempName.substr(0, limit);
		}

		return tempName;
	}
};
