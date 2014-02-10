#include "Engine.h"


Table* Engine::projection(string startTable, vector<string> variables){

	Table* oldTable = findTable(startTable);
	map< string, vector<Attribute*> > oldData = oldTable->getData();



	//TODO What should I name this?
	vector<string> newTypes;
	for (unsigned int i = 0; i < variables.size(); i++){

		newTypes.push_back(oldTable->getTypeOfColumn(variables[i]));
	}
	bool keyIncluded = false;
	for (unsigned int i = 0; i < variables.size(); i++){

		if (variables[i] == oldTable->getKeyName())
			keyIncluded = true;
	}
	Table* newtable;
	if (keyIncluded)
		newtable = new Table(oldTable->getTableName(), oldTable->getKeyName(), newTypes, variables);
	else
		newtable = new Table(oldTable->getTableName(), variables[0], newTypes, variables);

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