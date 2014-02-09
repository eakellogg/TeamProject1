#include "Engine.h"
#include "ConditionEval.h"


void  Engine::update(string tableName, vector< tuple<string, string> > namevarpairs, ConditionTree t){


	//TODO This needs to remove the row and reinsert it if the key changes. 
	Table* table = findTable(tableName);

	map < string, vector<Attribute* > > data = table->getData();

	map< string, vector<Attribute* > >::iterator it = data.begin();

	for (
		map< string, vector<Attribute* > >::iterator it = data.begin();
		it != data.end(); it++)
	{

		table->setCurrentRow(it->second);
		if ( table->EvalConditionTree(&t) == TRUE )
		{
			for ( unsigned int i = 0; i < namevarpairs.size(); i++)
			{
				try{
					Attribute* a = table->getVariable(get<0>(namevarpairs[i]));

					a->setValue(get<1>(namevarpairs[i]));
				}
				catch (...)
				{
					cout << "Incorrect Varaible name assignment";
				}
				
			}
		}
	}

}