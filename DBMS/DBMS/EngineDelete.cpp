#include "Engine.h"

using namespace std;

// delete a table from the database
void Engine::deleteFrom(Table* table, ConditionTree t){
	//TODO This needs to remove the row and reinsert it if the key changes. 
	map < string, vector<Attribute* > > data = table->getData();

	map< string, vector<Attribute* > >::iterator it = data.begin();

	for (map< string, vector<Attribute* > >::iterator it = data.begin(); it != data.end(); it++) {
		table->setCurrentRow(it->second);
		if ( table->EvalConditionTree(&t) == TRUE )	{
			table->deleteRow(it->first);
		}
	}
}