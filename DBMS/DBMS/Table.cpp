#pragma once

#include "Table.h"

using namespace std;



	/*********************************************************************************
	constructor
	*********************************************************************************/


	Table::Table(string tableName, string keyName, vector<string> columnTypes, vector<string> columnTitles)
		:tableName(tableName), keyName(keyName), columnTypes(columnTypes), columnTitles(columnTitles)
	{	}


	/*********************************************************************************
	non-modifying functions / accessor methods
	*********************************************************************************/


	string Table::getTableName() { return tableName; }

	string Table::getKeyName() { return keyName; }

	map< string, vector<Attribute*> > Table::getData() { return data; }

	vector<string> Table::getColumnTypes() { return columnTypes; }

	vector<string> Table::getColumnTitles() { return columnTitles; }

	vector<Attribute*> Table::getCurrentRow() { return currentRow; }


	/*********************************************************************************
	modifying functions
	*********************************************************************************/


	// add a row to the table
	void Table::addRow(vector<Attribute*> row, vector<string> columnTypes) {
		if (checkMatchingTypes(columnTypes)) {
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
	void Table::deleteRow(string key) {
		try {
			data.erase(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}
	}


	// find and return a specific row in the table
	vector<Attribute*> Table::getRow(string key) {
		try {
			return data.at(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}
	}


	// find and return a specific item in a specific row in the table
	Attribute* Table::getItem(string key, string columnName) {
		try {
			currentRow = data.at(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}

		
		// search the temporary row for correct item based on column name
		for (unsigned int i = 0; i < (columnTitles.size() - 1); i++) {
			if (columnTitles[i] == columnName) {
				return currentRow[i];
			}
		}
		throw "column does not exist";
	}


	// takes in a column name, searches the current row, and returns the value of the column name
	Attribute* Table::getVariable(string columnName) {
		for (unsigned int i = 0; i < columnTitles.size(); i++) {
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
	void Table::resetCurrentRow() {
		currentRow = data.begin()->second;
	}


	// set the currentRow pointer appropriately with regards to the offset passed
	void Table::setCurrentRow(int offset) {
		auto iterator = data.begin();
		advance(iterator, offset);
		currentRow = (iterator)->second;
	}

	void Table::setCurrentRow(vector<Attribute*> row){
		currentRow = row;
	}

	// check to make sure the types of the table's rows and the passed types are equivalent
	bool Table::checkMatchingTypes(vector<string> rowTypes) {
		// check every type of the row in question and compare with table's row types
		for ( unsigned int i = 0; i < columnTypes.size(); i++) {
			if (rowTypes[i] != columnTypes[i]) {
				return false; // incorrect type was found in the process of adding
			}
		}
		return true;
	}


	// return the type associated with a column name
	string Table::getTypeOfColumn(string columnName) {
		// search all columns in the table by name
		for ( unsigned int i = 0; i < columnTitles.size(); i++) {
			if (columnTitles[i] == columnName) { // if a match is found, return the corresponding type
				return columnTypes[i];
			}
		}
		throw "column does not exist";
	}


	// print the table in an orderly format
	void Table::printTable() {
		cout << tableName << endl;

		// print the column names
		cout << "********************************************************************************************" << endl;
		for (unsigned int i = 0; i < columnTitles.size(); i++) {
			cout << left << setw(20) << formatString(columnTitles[i], 20);
		}
		cout << endl << "********************************************************************************************" << endl;
		auto iterator = data.begin();
		// print the data for each row, alligned with the appropriate column
		for ( unsigned int i = 0; i < data.size(); i++) {
			currentRow = iterator->second;
			// print every individual row's data,alligned with the appropriate column
			for (unsigned int j = 0; j < currentRow.size(); j++) {
				cout << left << setw(20) << formatString(currentRow[j]->getValue(), 20);
			}
			cout << endl;
			iterator++;
		}
		cout << endl;
	}


	// limit string's length to the specified limit for proper formatting
	string Table::formatString(string tempName, unsigned int limit) {
		if (tempName.length() > limit) {
			tempName = tempName.substr(0, limit);
		}

		return tempName;
	}
