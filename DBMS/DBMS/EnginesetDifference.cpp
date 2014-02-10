#pragma once

#include "Engine.h"

//in order to use a union operation the tables must be compatible
//they must have the same attributes
static bool unionCompatible(Table* firstTable, Table* secondTable) {
	vector<string> firstTableColumns = firstTable->getColumnTitles();
	vector<string> secondTableColumns = secondTable->getColumnTitles();

	if (firstTableColumns.size() != secondTableColumns.size())
		return false;

	for (unsigned int i = 0; i < firstTableColumns.size(); i++) { // iterate through all of first table columns
		bool isShared = false;
		for (unsigned int j = 0; j < secondTableColumns.size(); j++) { // iterate through all of second table columns
			if (firstTableColumns[i] == secondTableColumns[j]) { // if match is found between names, check type
				if (firstTable->getColumnTypes()[i] == secondTable->getColumnTypes()[j]) { // if name and type match, the attribute is shared
					isShared = true;
				}
			}
		}
		if (!isShared)  //no match was found to the column, not unionCompatible
			return false;
	}
	return true;
}


//helper function that makes sure if an instance is repeated in the two tables we do not put it in the difference
static bool matchingData(map<string, vector<Attribute*>> firstTableData, vector<Attribute*> secondTableRow) {
	//iterate through the first table data
	for (map<string, vector<Attribute*>>::iterator i = firstTableData.begin(); i != firstTableData.end(); i++) {
		bool isSame = true;
		for (unsigned int j = 0; j < secondTableRow.size(); j++) {
			//if any of the values dont match change isSame
			if (i->second[j]->getValue() != secondTableRow[j]->getValue()) {
				isSame = false;
			}
		}
		//if the rows matched, return that we had a match
		if (isSame)
		{
			return true;
		}
	}

	return false; //the data was not repeated in the first table
}


Table* Engine::setDifference(Table* firstTable, Table* secondTable) {

	if (!unionCompatible(firstTable, secondTable)) {
		throw "tables are not union compatible, thus difference cannot be performed";
	}

	vector<string> newColumnTitles;
	vector<string> newColumnTypes;

	vector<string> firstTableColumns = firstTable->getColumnTitles();
	// add all of first table's column names/types to the new table's column names/types
	//since they are union-compatible this is all we will need
	for (unsigned int i = 0; i < firstTableColumns.size(); i++) {
		newColumnTitles.push_back(firstTableColumns[i]);
		newColumnTypes.push_back(firstTable->getTypeOfColumn(firstTableColumns[i]));
	}

	string newKey = firstTable->getKeyName();

	// new table to add data to
	Table* newTable = new Table("Union Table", newKey, newColumnTypes, newColumnTitles);

	map<string, vector<Attribute*>> firstTableData = firstTable->getData();
	map<string, vector<Attribute*>> secondTableData = secondTable->getData();

	int firstTableOffset = 0;

	//add all of the first table data to the new table
	for (map<string, vector<Attribute*>>::iterator i = firstTableData.begin(); i != firstTableData.end(); i++) {
		vector<Attribute*> newRow;
		firstTable->setCurrentRow(firstTableOffset);
		if (!matchingData(secondTableData, firstTable->getCurrentRow())){
			for (unsigned int i = 0; i < firstTableColumns.size(); i++) {
				newRow.push_back(firstTable->getVariable(newColumnTitles[i]));
			}
			newTable->addRow(newRow, newColumnTypes);
		}
		firstTableOffset++;
	}

	return newTable;
}