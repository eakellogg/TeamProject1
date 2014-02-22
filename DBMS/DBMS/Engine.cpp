#pragma once

#include "Engine.h"
#include "Table.h"
#include <fstream>
#include <iostream>

using namespace std;
class std::Table;

/*********************************************************************************
	constructor
*********************************************************************************/


	//constructor
	Engine::Engine(DBMS* master) : master(master)
	{	}


/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	//we can remove this section if we find we don't need it
	vector<Table*> Engine::getTables() { return tables; }


/*********************************************************************************
	modifying functions
*********************************************************************************/

	// create a table with the row types and column titles given
	void Engine::createTable(string tableName, vector<string> keyName, vector<string> columnTypes, vector<string> columnTitles) {
		for (int i = 0; i < keyName.size(); i++) {
			if (find(columnTitles.begin(), columnTitles.end(), keyName[i]) == columnTitles.end()) {
				throw "key name does not match any column, table not created";
			}
		}
		tables.push_back(new Table(tableName, keyName, columnTypes, columnTitles));
	}


	// delete a table from the database
	void Engine::dropTable(Table* table) {
		// search database for a table with matching name; delete table if it exists
		for (unsigned int i = 0; i < tables.size(); i++) {
			if (tables[i]->getTableName() == table->getTableName()) {
				tables.erase(tables.begin() + i); // must use tables.begin() to get iterator; increment with i
				return;
			}
		}
		throw "table does not exist";
	}


	// insert a row into the table with the proper name
	void Engine::insertInto(Table* table, vector<Attribute*> row, vector<string> columnTypes) {
		table->addRow(row, columnTypes);
	}


	// insert a row into the table with the proper name
	void Engine::insertInto(Table* tablea, Table* tableb) {

		for (int i = 0; i < tablea->getColumnTitles().size(); i++) {
			if (tablea->getColumnTitles()[i] != tableb->getColumnTitles()[i]) {
				throw "tables cannot be added";
			}
			if (tablea->getColumnTypes()[i] != tableb->getColumnTypes()[i]) {
				throw "tables cannot be added";
			}
		}

		map< string, vector<Attribute*> > data = tableb->getData();
		for (map< string, vector<Attribute*> >::iterator it = data.begin(); it != data.end(); it++) {
			vector<Attribute*> newRow;
			vector<Attribute*> tempRow = it->second;
			for (int j = 0; j < tempRow.size(); j++) {
				Attribute* newAttribute = new Attribute(tempRow[j]->getType(), tempRow[j]->getValue());
				newRow.push_back(newAttribute);
			}
			tablea->addRow(newRow, tablea->getColumnTypes());
		}
	}


	// opens the file represented by tableName; reads the table into the database
	void Engine::openFile(string tableName) {
		vector<string> fileLines;

		ifstream infile(tableName + ".db");
		string tempLine;

		if (!infile.is_open()) {
			//no string returned because we dont want things to print when
			//checking if a file exists
			throw "";
		}

		while (getline(infile, tempLine))
		{
			fileLines.push_back(tempLine);
		}

		infile.close();
		master->load(fileLines);
	}

	// closes an open file, saving all changes that occured since opening; removes the table from the database
	void Engine::closeFile(Table* table) {
		fstream outfile(table->getTableName() + ".db");

		if (table == NULL) {
			throw "the file does not exist";
			return;
		}

		if (!outfile.is_open()) {
			throw "the file does not exist";
			return;
		}

		writeFile(table);

		dropTable(table);
		outfile.close();
	}

	// writes a new file for a table, overwritting an already existing file with the same name if there is one
	void Engine::writeFile(Table* table) {
		ofstream outfile(table->getTableName() + ".db", ofstream::trunc);

		if (!outfile.is_open()) {
			throw "the file could not be opened due to error";
		}

		vector<string> tempTypes = table->getColumnTypes();
		vector<string> tempTitles = table->getColumnTitles();

		outfile << "CREATE TABLE " << table->getTableName() << " (";
		for (int i = 0; i < tempTypes.size(); i++) {
			outfile << tempTitles[i];
			if (tempTypes[i] == STRING_LITERAL) {
				outfile << " VARCHAR(30)";
			}
			if (tempTypes[i] == INT_LITERAL) {
				outfile << " INTEGER";
			}
			if (i == tempTypes.size() - 1) {
				break;
			}
			outfile << ", ";
		}
		outfile << ") PRIMARY KEY (";
		
		for (int i = 0; i < table->getKeyName().size(); i++) {
			outfile << table->getKeyName()[i];
			if (i == table->getKeyName().size() - 1)
				break;
			outfile << ", ";
		}
		outfile << ");\n";

		auto data = table->getData();
		auto iterator = data.begin();
		vector<Attribute*> tempRow;

		// print the data for each row
		for (unsigned int i = 0; i < data.size(); i++) {
			tempRow = iterator->second;
			outfile << "INSERT INTO " << table->getTableName() << " VALUES FROM (";
			// print every individual row's data
			
			for (unsigned int j = 0; j < tempRow.size(); j++) {
				if (tempRow[j]->getType() == STRING_LITERAL) {
					outfile << '"' << tempRow[j]->getValue() << '"';
				}
				if (tempRow[j]->getType() == INT_LITERAL) {
					outfile << tempRow[j]->getValue();
				}
				if (j == tempRow.size() - 1) {
					break;
				}
				outfile << ", ";
			}
			outfile << ");\n";
			iterator++;
		}
		outfile.close();
	}


	// show a relation by printing the table representing it
	void Engine::show(Table* table) {
		table->printTable();
	}


/*********************************************************************************
	helper functions
*********************************************************************************/


	// search database for a table with matching name
	Table* Engine::findTable(string tableName) {
		// compare passed name to names of all tables in the database
		for (unsigned int i = 0; i < tables.size(); i++) {
			if (tables[i]->getTableName() == tableName) {
				return tables[i];
			}
		}
		//throw "table does not exist"; // throwing exception prevents needing checks for unfound tables in other functions
		return NULL;
	}
