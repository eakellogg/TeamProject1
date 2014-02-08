#pragma once

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include <map>

#include "Attribute.h"

using namespace std;


class Table {
	string tableName;
	map< string, vector<Attribute*> > data; // the rows of the table
	vector<string> columnTypes;
	vector<string> columnTitles;
	vector<Attribute*> currentRow;
public:
/*********************************************************************************
	constructor
*********************************************************************************/


	Table(string tableName, vector<string> columnTypes, vector<string> columnTitles)
		:tableName(tableName), columnTypes(columnTypes), columnTitles(columnTitles)
	{	}


/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	string getTableName() { return tableName; }

	map< string, vector<Attribute*> > getData() { return data; }

	vector<string> getColumnTypes() { return columnTypes; }

	vector<string> getColumnTitles() { return columnTitles; }

	vector<Attribute*> getCurrentRow() { return currentRow; };


/*********************************************************************************
	modifying functions
*********************************************************************************/


	// add a row to the table
	void addRow(string key, vector<Attribute*> row, vector<string> rowTypes) {
		if (checkMatchingTypes(rowTypes)) {
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


	// takes in a variable name, searches the current row, and returns the value of the variable name
	Attribute* getVariable(string variableName) {
		for (int i = 0; i < columnTitles.size(); i++) {
			if (columnTitles[i] == variableName) {
				return currentRow[i];
			}
		}
		throw "variable does not exist";
	}


/*********************************************************************************
	helper functions
*********************************************************************************/


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
};
