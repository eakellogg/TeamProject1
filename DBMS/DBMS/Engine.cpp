#pragma once

#include "Engine.h"
#include <fstream>
#include <iostream>

using namespace std;

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
	void Engine::createTable(string tableName, string keyName, vector<string> columnTypes, vector<string> columnTitles) {
		if (find(columnTitles.begin(), columnTitles.end(), keyName) == columnTitles.end()) {
			throw "key name does not match any column, table not created";
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


	// opens the file represented by tableName; reads the table into the database
	vector<string> Engine::openFile(string tableName) {
		vector<string> fileLines;

		ifstream infile(tableName + ".db");
		string tempLine;

		if (!infile.is_open()) {
			throw "the file does not exist";
		}

		while (getline(infile, tempLine))
		{
			fileLines.push_back(tempLine);
		}

		infile.close();
		return fileLines;
	}

	// closes an open file, saving all changes that occured since opening; removes the table from the database
	void Engine::closeFile(Table* table) {
		fstream outfile(table->getTableName() + ".db");

		if (!outfile.is_open()) {
			throw "the file does not exist";
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
			if (tempTypes[i] == STRING_TYPE) {
				outfile << " VARCHAR(30)";
			}
			if (tempTypes[i] == INT_TYPE) {
				outfile << " INTEGER";
			}
			if (i == tempTypes.size() - 1) {
				break;
			}
			outfile << ", ";
		}
		outfile << ") PRIMARY KEY (" << table->getKeyName() << ");\n";

		auto data = table->getData();
		auto iterator = data.begin();
		vector<Attribute*> tempRow;
		// print the data for each row
		for (unsigned int i = 0; i < data.size(); i++) {
			tempRow = iterator->second;
			outfile << "INSERT INTO " << table->getTableName() << " VALUES FROM (";
			// print every individual row's data
			for (unsigned int j = 0; j < tempRow.size(); j++) {
				if (tempRow[j]->getType() == STRING_TYPE) {
					outfile << '"' << tempRow[j]->getValue() << '"';
				}
				if (tempRow[j]->getType() == INT_TYPE) {
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
		throw "table does not exist"; // throwing exception prevents needing checks for unfound tables in other functions
	}
