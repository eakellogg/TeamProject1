#include "Engine.h"

// delete a table from the database
void Engine::deleteFrom(string tableName, ConditionTree t){
	//TODO This needs to remove the row and reinsert it if the key changes. 
	Table* table = findTable(tableName);

	map < string, vector<Attribute* > > data = table->getData();

	map< string, vector<Attribute* > >::iterator it = data.begin();

	for (map< string, vector<Attribute* > >::iterator it = data.begin(); it != data.end(); it++) {
		table->setCurrentRow(it->second);
		if ( table->EvalConditionTree(&t) == TRUE )	{
			table->deleteRow(it->first);
		}
	}
}