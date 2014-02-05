#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>

#include "Table.h"

using namespace std;


class Engine {
	vector<Table> tables;

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


/*********************************************************************************
	modifying functions
*********************************************************************************/


	void createTable(string tableName, vector<string> types, vector<string> columnTitles) {
		tables.push_back(Table(tableName, types, columnTitles));
	}


	void deleteTable(string tableName) {
		// search database for a table with matching name; delete table if it exists
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i].getTableName() == tableName) {
				tables.erase[i];
				break;
			}
		}
	}


	void insertInto(string tableName, vector<string> row, vector<string> rowTypes) {
		// search database for a table with matching name; add row to correct table if it exists
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i].getTableName() == tableName) {
				tables[i].addRow(row, rowTypes);
				break;
			}
		}
	}


	void update() {

	}


	void deleteFrom() {

	}
};
