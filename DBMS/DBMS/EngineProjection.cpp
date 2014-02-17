#include "Engine.h"

// calculates the projection of the given table and returns a new table with the result
Table* Engine::projection(Table* oldTable, vector<string> variables){

	map< string, vector<Attribute*> > oldData = oldTable->getData();



	//TODO What should I name this?
	vector<string> newTypes;
	for (unsigned int i = 0; i < variables.size(); i++){

		newTypes.push_back(oldTable->getTypeOfColumn(variables[i]));
	}

	bool keyIncluded = false;
	vector<string> newKey;

	for (unsigned int i = 0; i < variables.size(); i++){
		for (int j = 0; j < oldTable->getKeyName().size(); j++) {
			if (variables[i] == oldTable->getKeyName()[j]) {
				keyIncluded = true;
				newKey.push_back(variables[i]);
			}
		}
	}

	Table* newtable;
	if (keyIncluded)
		newtable = new Table(oldTable->getTableName(), newKey, newTypes, variables);
	else
		newtable = new Table(oldTable->getTableName(), vector<string>{variables[0]}, newTypes, variables);

	for (map< string, vector<Attribute*> >::iterator it = oldData.begin();
		it != oldData.end(); it++) {

		oldTable->setCurrentRow(it->second);
		vector<Attribute*> oldRow = it->second;
		vector<Attribute*> newRow;

		for (unsigned int i = 0; i < variables.size(); i++)
		{
			Attribute* a = new Attribute(newtable->getTypeOfColumn(variables[i]),
				oldTable->getVariable(variables[i])->getValue());

			newRow.push_back(a);
		}
		newtable->addRow(newRow, newtable->getColumnTypes());
	}
	return newtable;
}