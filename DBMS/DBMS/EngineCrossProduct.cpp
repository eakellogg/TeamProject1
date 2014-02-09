#pragma once

#include "Engine.h"

// make and return a new row with the naturally joined information
static vector<Attribute*> fillNewRow(Table* firstTable, Table* secondTable, vector<string> newColumnTitles, int identifierCount) {
	vector<Attribute*> newRow;

	// get all needed data from first table
	for (int i = 0; i < firstTable->getColumnTitles().size(); i++) {
		newRow.push_back(firstTable->getVariable(newColumnTitles[i]));
	}
	// get all needed data from second table
	for (int j = firstTable->getColumnTitles().size(); j < newColumnTitles.size() - 1; j++) {
		newRow.push_back(secondTable->getVariable(newColumnTitles[j]));
	}

	Attribute* identifier = new Attribute("int", to_string(identifierCount));
	newRow.push_back(identifier);

	return newRow;
}


Table* Engine::crossProduct(Table* firstTable, Table* secondTable) {
	vector<string> firstTableColumns = firstTable->getColumnTitles();
	vector<string> secondTableColumns = secondTable->getColumnTitles();

	vector<string> newColumnTitles;
	vector<string> newColumnTypes;

	// add all of first table's column names/types to the new table's column names/types
	for (int i = 0; i < firstTableColumns.size(); i++) {
		newColumnTitles.push_back(firstTableColumns[i]);
		newColumnTypes.push_back(firstTable->getTypeOfColumn(firstTableColumns[i]));
	}

	// add all of second table's column names/types to the new table's column names/types
	for (int j = 0; j < secondTableColumns.size(); j++) {
			newColumnTitles.push_back(secondTableColumns[j]);
			newColumnTypes.push_back(secondTable->getTypeOfColumn(secondTableColumns[j]));
	}

	string newKey = firstTable->getTableName() + secondTable->getTableName();
	newColumnTitles.push_back(newKey);
	newColumnTypes.push_back("int");

	// new table to add data to
	Table* newTable = new Table("New Table", newKey, newColumnTypes, newColumnTitles);

	int firstTableOffset = 0;
	int secondTableOffset = 0;
	int identifierCount = 0;
	map<string, vector<Attribute*>> firstTableData = firstTable->getData();
	map<string, vector<Attribute*>> secondTableData = secondTable->getData();

	// iterate through all rows of the first table
	for (map<string, vector<Attribute*>>::iterator i = firstTableData.begin(); i != firstTableData.end(); i++) {
		firstTable->setCurrentRow(firstTableOffset); // set current row of first table to correct row

		// for each rows of first table, iterate through all rows of the second table
		for (auto j = secondTableData.begin(); j != secondTableData.end(); j++) {
			secondTable->setCurrentRow(secondTableOffset); // set current row of second table to correct row

			// combine all data among the two rows
			vector<Attribute*> newRow = fillNewRow(firstTable, secondTable, newColumnTitles, identifierCount);
			identifierCount++;
			newTable->addRow(newRow, newColumnTypes);
			
			secondTableOffset++;
		}
		secondTableOffset = 0;
		firstTableOffset++;
	}
	return newTable;
}