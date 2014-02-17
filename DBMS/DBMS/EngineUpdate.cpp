#include "Engine.h"
#include "ConditionEval.h"
#include "Constants.h"

void Engine::update(Table* table, vector< tuple<string, string> > namevarpairs, ConditionTree t){


	//TODO This needs to remove the row and reinsert it if the key changes. 
	map < string, vector<Attribute* > > data = table->getData();

	map< string, vector<Attribute* > >::iterator it = data.begin();
	vector<string> rowstoremove;
	bool keyChanged = false;

	for (unsigned int i = 0; i < namevarpairs.size(); i++) 
	{
		for (int j = 0; j < table->getKeyName().size(); j++) {
			if (get<0>(namevarpairs[i]) == table->getKeyName()[j])
				keyChanged = true;
		}
	}

	for (map< string, vector<Attribute* > >::iterator it = data.begin(); it != data.end(); it++) 
	{
		table->setCurrentRow(it->second);
		if (table->EvalConditionTree(&t) == TRUE)
		{
			if (!keyChanged)
			{
				for (unsigned int i = 0; i < namevarpairs.size(); i++)
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
			else
			{
				vector<Attribute*> oldrow = table->getCurrentRow();
				rowstoremove.push_back(it->first);
				vector<Attribute*> newrow;
				vector<string> types = table->getColumnTypes();
				for (unsigned int i = 0; i < oldrow.size(); i++)
				{
					Attribute* old = oldrow[i];
					Attribute* newA = new Attribute(old->getType(), old->getValue());
					newrow.push_back(newA);

				}
				table->setCurrentRow(newrow);
				for (unsigned int i = 0; i < namevarpairs.size(); i++)
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
				table->addRow(newrow, types);
			}
		}
		for (unsigned int i = 0; i < rowstoremove.size(); i++){
			table->deleteRow(rowstoremove[i]);
		}
	}
}