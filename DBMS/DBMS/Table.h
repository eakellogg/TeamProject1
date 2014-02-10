#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include <map>
#include <iomanip>
#include "ConditionTree.h"
#include "Attribute.h"

using namespace std;

const static string INT_TYPE = "INT";
const static string STRING_TYPE = "STRING";

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

	Table(string tableName, string keyName, vector<string> columnTypes, vector<string> columnTitles);

	Table(Table* table);

/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	string getTableName();

	string getKeyName();

	map< string, vector<Attribute*> > getData();

	vector<string> getColumnTypes();

	vector<string> getColumnTitles();

	vector<Attribute*> getCurrentRow();

	string EvalConditionTree(ConditionTree* tree);

	tuple<string, string> NodeEval(ConditionTree::Node* n);


/*********************************************************************************
	modifying functions
*********************************************************************************/

	// add a row to the table
	void addRow(vector<Attribute*> row, vector<string> columnTypes);

	// delete a row from the table
	void deleteRow(string key);

	// rename a column
	void renameColumn(int column, string name);

	// find and return a specific row in the table
	vector<Attribute*> getRow(string key);

	// find and return a specific item in a specific row in the table
	Attribute* getItem(string key, string columnName);

	// takes in a column name, searches the current row, and returns the value of the column name
	Attribute* getVariable(string columnName);
	
/*********************************************************************************
	helper functions
*********************************************************************************/

	// reset the currentRow pointer to the beginning of the map
	void resetCurrentRow();

	// set the currentRow pointer appropriately with regards to the offset passed
	void setCurrentRow(int offset);

	//set the currentRow point to this row object passed very dangerous!!! 
	void setCurrentRow(vector<Attribute*>);

	// check to make sure the types of the table's rows and the passed types are equivalent
	bool checkMatchingTypes(vector<string> rowTypes);

	// return the type associated with a column name
	string getTypeOfColumn(string columnName); 
	
	// print the table in an orderly format
	void printTable();

	// limit string's length to the specified limit for proper formatting
	string formatString(string tempName, unsigned int limit);

	//Comparion of strings as if they were integers
	int compareStringInts(string lv, string rv);
};

#endif