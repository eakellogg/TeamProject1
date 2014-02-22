#pragma once

#include "Table.h"

using namespace std;

/*********************************************************************************
	constructor
*********************************************************************************/


	Table::Table():tableName("EmptyTable"){	}

	Table::Table(string tableName, vector<string> keyName, vector<string> columnTypes, vector<string> columnTitles)
		:tableName(tableName), keyName(keyName), columnTypes(columnTypes), columnTitles(columnTitles)
	{	}


	Table::Table(Table* table) {
		tableName = "new" + table->getTableName();
		keyName = table->getKeyName();
		for (int i = 0; i < table->getColumnTitles().size(); i++) {
			columnTitles.push_back(table->getColumnTitles()[i]);
			columnTypes.push_back(table->getColumnTypes()[i]);
		}

		map< string, vector<Attribute*> > data = table->getData();
		for (map< string, vector<Attribute*> >::iterator it = data.begin(); it != data.end(); it++) {
			vector<Attribute*> newRow;
			vector<Attribute*> tempRow = it->second;
			for (int j = 0; j < tempRow.size(); j++) {
				Attribute* newAttribute = new Attribute(tempRow[j]->getType(), tempRow[j]->getValue());
				newRow.push_back(newAttribute);
			}
			addRow(newRow, table->getColumnTypes());
		}
	}

/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	string Table::getTableName() { return tableName; }

	vector<string> Table::getKeyName() { return keyName; }

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
			string fullKey;
			for (int i = 0; i < keyName.size(); i++) {
				fullKey += getVariable(keyName[i])->getValue();
			}
			data.insert(make_pair(fullKey, row));
			return;
		}
		throw "types do not match";
	}

	
	// delete a row from the table
	void Table::deleteRow(string key) {
		try {
			data.erase(key);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}
	}


	//rename a column. If that column is the key, update keyName.
	void Table::renameColumn(int column, string name) {
		try {
			for (int i = 0; i < keyName.size(); i++) {
				cout << "!" << columnTitles[column] << " " << keyName[i] << " ";
				if (columnTitles[column] == keyName[i]) {
					cout << name << endl;
					keyName[i] = name;
				}
				cout << endl;
			}
			columnTitles[column] = name;
		}
		catch (out_of_range) {
			throw "column does not exist";
		}
	}


	// find and return a specific row in the table
	vector<Attribute*> Table::getRow(vector<string> key) {
		try {
			string fullKey;
			for (int i = 0; i < key.size(); i++) {
				fullKey += key[i];
			}
			return data.at(fullKey);
		}
		catch (out_of_range) {
			throw "key does not exist";
		}
	}


	// find and return a specific item in a specific row in the table
	Attribute* Table::getItem(vector<string> key, string columnName) {
		try {
			string fullKey;
			for (int i = 0; i < key.size(); i++) {
				fullKey += key[i];
			}
			currentRow = data.at(fullKey);
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


	// set the currentRow pointer appropriately with regards to the passed row
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
		printBorder(columnTitles.size());
		for (unsigned int i = 0; i < columnTitles.size(); i++) {
			cout << left << setw(20) << formatString(columnTitles[i], 20);
		}
		cout << endl;
		printBorder(columnTitles.size());
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


	// print the correct border for the table
	void Table::printBorder(int numAttributes) {
		for (int i = 0; i < numAttributes; i++) {
			cout << "*********************";
		}
		cout << endl;
	}
