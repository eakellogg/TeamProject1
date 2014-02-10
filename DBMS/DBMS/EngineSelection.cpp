#include "Engine.h"


Table* Engine::selection(string tableName, ConditionTree t){

	Table* oldtable = findTable(tableName);
	map< string, vector<Attribute*> > oldData = oldtable->getData();

	//TODO WHAT SHOULD I NAME THIS?
	Table* newtable = new Table(oldtable->getTableName(), oldtable->getKeyName(), oldtable->getColumnTypes(), oldtable->getColumnTitles());


	for ( map< string, vector<Attribute*> >::iterator it = oldData.begin();
		it != oldData.end(); it++) {

		string result;
		cout << "This is the name of this row  " << it->second[0]->getValue() << endl;
		result = oldtable->EvalConditionTree(&t);
		cout << "This is what the evaluation of that row results in " << result << endl;
		if (result == TRUE){
			
			oldtable->setCurrentRow(it->second);
			vector<Attribute*> oldRow  = it->second;
			vector<Attribute*> newRow;
			for (unsigned int i = 0; i < oldRow.size(); i++)
			{
				Attribute* a = new Attribute(oldRow[i]->getType(), oldRow[i]->getValue());
				newRow.push_back(a);
			}
			newtable->addRow(newRow , oldtable->getColumnTypes());
		}
	}

	return newtable;

}