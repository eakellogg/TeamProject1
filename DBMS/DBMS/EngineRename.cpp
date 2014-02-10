#include "Engine.h"

void Engine::rename(string tableName, vector<string> attributes) {
	Table* table = findTable(tableName);

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
}