#include "Engine.h"

// rename a given table and return a new table with the result
Table* Engine::rename(Table* oldTable, vector<string> attributes) {

	Table* table = new Table((*oldTable));

	vector<string> columnTitles = table->getColumnTitles();

	if (attributes.size() != columnTitles.size()) {
		throw "incorrect number of attributes to rename";
	}

	for (int i = 0; i < columnTitles.size(); i++) {
		if (columnTitles[i] != attributes[i]) {
			//rename the column. If the column was the key, update keyName
			table->renameColumn(i, attributes[i]);
		}
	}
	return table;
}