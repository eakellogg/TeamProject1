#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>

using namespace std;


class Table {
	string tableName;
	vector< vector<string> > data;
	vector<string> types;
	vector<string> columnTitles;

public:
/*********************************************************************************
	constructor
*********************************************************************************/
	

	Table(string tableName, vector<string> types, vector<string> columnTitles)
		:tableName(tableName), types(types), columnTitles(columnTitles)
	{	}


/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	string getTableName() { return tableName; }
	
	
/*********************************************************************************
	modifying functions
*********************************************************************************/


	// add a row to the table
	void addRow(vector<string> row, vector<string> rowTypes) {
		if (checkMatchingTypes(rowTypes)) {
			data.push_back(row);
		}
		return;
	}


	// update an already existing row
	void updateRow(vector<string> newRow, vector<string> rowTypes, int pos) { // need diff. than pos
		if (checkMatchingTypes(rowTypes)) {
			data[pos] = newRow;
		}
	}


	// delete a row from the table
	void deleteRow(int pos) {
		data.erase(data.begin() + pos); // must use data.begin() to get iterator; increment with pos
		return;
	}


	// find and return a specific row in the table
	vector<string> getRow(int pos) {
		return data[pos];
	}


	// find and return a specific item in a specific row in the table
	string getItem(string columnName, int pos) {
		vector<string> tempRow = data[pos];

		// search the row for correct item based on column name
		for (int i = 0; i < columnTitles.size(); i++) {
			if (columnName == columnTitles[i]) {
				return tempRow[i];
			}
		}
	}


/*********************************************************************************
	helper functions
*********************************************************************************/


	// check to make sure the types of the table's rows and the passed types are equivalent
	bool checkMatchingTypes(vector<string> rowTypes) {
		// check every type of the row in question and compare with table's row types
		for (int i = 0; i < types.size(); i++) {
			if (rowTypes[i] != types[i]) {
				return false; // incorrect type was found in the process of adding
			}
		}
		return true;
	}
};
