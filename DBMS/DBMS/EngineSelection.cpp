#include "Engine.h"

// proform a selection on the given table and return a new table with the result
Table* Engine::selection(Table* oldTable, ConditionTree t){

	map< string, vector<Attribute*> > oldData = oldTable->getData();

	//TODO WHAT SHOULD I NAME THIS?
	Table* newtable = new Table(oldTable->getTableName(), oldTable->getKeyName(), oldTable->getColumnTypes(), oldTable->getColumnTitles());


	for ( map< string, vector<Attribute*> >::iterator it = oldData.begin();
		it != oldData.end(); it++) {

		string result;
		oldTable->setCurrentRow(it->second);
		result = oldTable->EvalConditionTree(&t);
		if (result == TRUE){
			
			vector<Attribute*> oldRow  = it->second;
			vector<Attribute*> newRow;

			for (unsigned int i = 0; i < oldRow.size(); i++)
			{
				Attribute* a = new Attribute(oldRow[i]->getType(), oldRow[i]->getValue());
				newRow.push_back(a);
			}
			newtable->addRow(newRow , oldTable->getColumnTypes());
		}
	}
	return newtable;
}
