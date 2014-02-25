#pragma once

#include "Evaluator.h"
#include "EvaluationTree.h"

using namespace std;

//Evalutor Constuctor takes in pointers to the engine and queryHandler that it works with
//creates the map that will hold queries
Evaluator::Evaluator(Engine* dbms, QueryHandler* QH) : DBMS(dbms), queryHandle(QH)
{
	views = map<string, Table*>();
}

//Evaluates whatever tree you pass it by calling the correct engine calls
Table* Evaluator::Evaluate(EvaluationTree* tree)
{
	try {
		EvaluationTree::Node* root = tree->getRoot();

		//if the sql input is a query
		if (root->getType() == QUERY){
			EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
			EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

			//if the children are of the correct types
			if (leftChild->getType() == RELATION_NAME)
			{
				if (rightChild->getType() == EXPR)
				{
					//insert the query into storage map and return the resultant table
					EvaluationTree expressionTree = EvaluationTree(rightChild);
					Table* expressionTable = Evaluate(&expressionTree);
					string* value = (string*)(leftChild->getValue());

					map<string, Table*>::iterator it = views.find(*value);
					if (it != views.end())
						views.erase(it);
					views.insert(make_pair(*value, expressionTable));
					return expressionTable;
				}
			}
			throw("Wrong QUERY types");
		}

		//if the sql input is some kind of expression
		if (root->getType() == EXPR)
		{
			string* value = (string*)(root->getValue());

			//if the sql input is a selection expression
			if (*value == SELECTION_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() == CONDITION_TREE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass a table pointer and condition tree to the engine function
						//return resultant table
						EvaluationTree expressionTree = EvaluationTree(rightChild);
						Table* expressionTable = Evaluate(&expressionTree);
						if (expressionTable != NULL){
							ConditionTree* condTree = (ConditionTree*)(leftChild->getValue());
							Table* tbl = DBMS->selection(expressionTable, *condTree);
							return tbl;
						}
					}
				}
				//we now use selection to see if file already exists so string printed here is unwanted
				throw("");
			}

			//if the sql input is a projection expression
			if (*value == PROJECTION_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() == ATTRIBUTE_LIST)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass a table pointer and a list of attributes to the engine function
						//return resultant table
						EvaluationTree expressionTree = EvaluationTree(rightChild);
						Table* expressionTable = Evaluate(&expressionTree);
						if (expressionTable != NULL){
							vector<string>* variables = (vector<string>*)(leftChild->getValue());
							return DBMS->projection(expressionTable, *variables);
						}
					}
				}
				throw("Wrong types in projection");
			}

			//if the sql input is a renaming expression
			if (*value == RENAMING_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() == ATTRIBUTE_LIST)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass a table pointer and the new attribute names to the engine function
						//return resultant table
						EvaluationTree expressionTree = EvaluationTree(rightChild);
						Table* expressionTable = Evaluate(&expressionTree);
						if (expressionTable != NULL){
							vector<string>* attributes = (vector<string>*)(leftChild->getValue());
							return DBMS->rename(expressionTable, *attributes);
						}
					}
				}
				throw("Wrong types in renaming");
			}

			//if the sql input is a set union expression
			if (*value == UNION_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() != PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass table pointers to the engine function
						//return resultant table
						EvaluationTree expressionTreeRight = EvaluationTree(rightChild);
						Table* expressionTableRight = Evaluate(&expressionTreeRight);
						if (expressionTableRight != NULL){
							EvaluationTree expressionTreeLeft = EvaluationTree(leftChild);
							Table* expressionTableLeft = Evaluate(&expressionTreeLeft);
							if (expressionTableLeft != NULL){
								return DBMS->setUnion(expressionTableLeft, expressionTableRight);
							}
						}
					}
				}
				throw("Wrong types in union");
			}

			//if the sql input is a set difference expression
			if (*value == DIFFERENCE_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() != PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass table pointers to the engine function
						//return resultant table
						EvaluationTree expressionTreeRight = EvaluationTree(rightChild);
						Table* expressionTableRight = Evaluate(&expressionTreeRight);
						if (expressionTableRight != NULL){
							EvaluationTree expressionTreeLeft = EvaluationTree(leftChild);
							Table* expressionTableLeft = Evaluate(&expressionTreeLeft);
							if (expressionTableLeft != NULL){
								return DBMS->setDifference(expressionTableLeft, expressionTableRight);
							}
						}
					}
				}
				throw("Wrong types in difference");
			}

			//if the sql input is a cross product expression
			if (*value == PRODUCT_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() != PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass table pointers to the engine function
						//return resultant table
						EvaluationTree expressionTreeRight = EvaluationTree(rightChild);
						Table* expressionTableRight = Evaluate(&expressionTreeRight);
						if (expressionTableRight != NULL){
							EvaluationTree expressionTreeLeft = EvaluationTree(leftChild);
							Table* expressionTableLeft = Evaluate(&expressionTreeLeft);
							if (expressionTableLeft != NULL){
								return DBMS->crossProduct(expressionTableLeft, expressionTableRight);
							}
						}
					}
				}
				throw("Wrong types in crossProduct");
			}

			//if the sql input is a natural join expression
			if (*value == JOIN_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (leftChild->getType() != PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						//pass table pointers to the engine function
						//return resultant table
						EvaluationTree expressionTreeRight = EvaluationTree(rightChild);
						Table* expressionTableRight = Evaluate(&expressionTreeRight);
						if (expressionTableRight != NULL){
							EvaluationTree expressionTreeLeft = EvaluationTree(leftChild);
							Table* expressionTableLeft = Evaluate(&expressionTreeLeft);
							if (expressionTableLeft != NULL){
								return DBMS->naturalJoin(expressionTableLeft, expressionTableRight);
							}
						}
					}
				}
				throw("Wrong types in naturalJoin");
			}
		}

		//if the sql input is a relation name
		if (root->getType() == RELATION_NAME){
			//first look if it is a query view in our local map
			string* tableName = (string*)(root->getValue());
			auto mapIter = views.find(*tableName);
			if (mapIter != views.cend())
			{
				return mapIter->second;
			}

			//if not try to see if the engine is storing it
			return DBMS->findTable(*tableName);

			throw("relation name not valid");
		}

		//if the sql input is a command
		if (root->getType() == COMMAND_OPERATOR)
		{
			string* value = (string*)(root->getValue());

			//if the sql input is a open command
			if (*value == OPEN)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];

				//if the children are of the correct types
				if (child->getType() == RELATION_NAME)
				{
					DBMS->openFile(*(string*)child->getValue());
					return NULL;
				}
				throw("Wrong values in OPEN");
			}

			//if the sql input is a write command
			if (*value == WRITE)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];

				//if the children are of the correct types
				if (child->getType() == RELATION_NAME)
				{
					//pass table pointer to the engine function
					//return nothing
					EvaluationTree expressionTree = EvaluationTree(child);
					Table* expressionTable = Evaluate(&expressionTree);

					if (expressionTable != NULL)
					{
						DBMS->writeFile(expressionTable);
						return NULL;
					}
				}
				throw("Wrong values in WRITE");
			}

			//if the sql input is a close command
			if (*value == CLOSE)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];

				//if the children are of the correct types
				if (child->getType() == RELATION_NAME)
				{
					//pass a table pointer to the engine function
					//return nothing
					EvaluationTree expressionTree = EvaluationTree(child);
					Table* expressionTable = Evaluate(&expressionTree);
					if (expressionTable != NULL)
					{
						DBMS->closeFile(expressionTable);
						return NULL;
					}
				}
				//throw "Wrong values in CLOSE";
			}

			//if the sql input is a exit command
			if (*value == EXIT)
			{
				//drop all tables 
				//those not already stored in files will be lost
				vector<Table*> tables = DBMS->getTables();
				for (int i = tables.size() - 1; i >= 0; i--)
				{
					DBMS->dropTable(tables[i]);
				}
				return NULL;
			}

			//if the sql input is a show command
			if (*value == SHOW)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];

				//if the children are of the correct types
				if (child->getType() == RELATION_NAME)
				{
					//pass a table pointer to the engine function
					//return nothing, table will be printed
					EvaluationTree expressionTree = EvaluationTree(child);
					Table* expressionTable = Evaluate(&expressionTree);

					if (expressionTable != NULL)
					{
						DBMS->show(expressionTable);
						return NULL;
					}
				}
				throw "Wrong values in SHOW";
			}

			//if the sql input is a create table command
			if (*value == CREATE_TABLE)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childColumns = (*(root->getChildren()))[1];
				EvaluationTree::Node* childKeys = (*(root->getChildren()))[2];

				//if the children are of the correct types
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childColumns->getType() == ATTRIBUTE_TYPE_PAIR_LIST)
					{
						if (childKeys->getType() == ATTRIBUTE_LIST)
						{
							//retrieve table name and keys
							//slit the tuple column vector into names and types vector
							string* tableName = (string*)(childTableName->getValue());
							vector<tuple <string, string>>* columns = (vector<tuple <string, string>>*)(childColumns->getValue());
							vector<string> columnTypes = vector<string>();
							vector<string> columnNames = vector<string>();
							for (int i = 0; i < columns->size(); i++)
							{
								columnTypes.push_back(get<0>((*columns)[i]));
								columnNames.push_back(get<1>((*columns)[i]));
							}
							vector<string>* keys = (vector<string>*)(childKeys->getValue());

							//pass in tableName, columnNames, columnTypes, and keys to engine
							DBMS->createTable(*tableName, *keys, columnTypes, columnNames);

							//return nothing
							return NULL;
						}
					}
				}
				throw("Wrong types in CREATE");
			}

			//if the sql input is a insert table command
			if (*value == INSERT)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childLiteralList = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childLiteralList->getType() == LITERAL_LIST)
					{
						//retrieve table pointer
						//slit the tuple attribute vector into values and types vector
						string* tableName = (string*)(childTableName->getValue());
						Table* insertTable = DBMS->findTable(*tableName);
						vector<tuple <string, string>>* literalList = (vector<tuple <string, string>>*)(childLiteralList->getValue());
						vector<string> literalTypes = vector<string>();
						vector<Attribute*> literalValues = vector<Attribute*>();
						for (int i = 0; i < literalList->size(); i++)
						{
							Attribute* newAttribute = new Attribute(get<0>((*literalList)[i]), get<1>((*literalList)[i]));
							literalTypes.push_back(get<0>((*literalList)[i]));
							literalValues.push_back(newAttribute);
						}

						//pass in the table, values, and types to engine
						DBMS->insertInto(insertTable, literalValues, literalTypes);
						//insertTable->printTable();
						//return nothing
						return NULL;
					}
				}
				throw("Wrong types in INSERT");
			}

			//if the sql input is a delete command
			if (*value == DELETE)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childCondTree = (*(root->getChildren()))[1];

				//if the children are of the correct types
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childCondTree->getType() == CONDITION_TREE)
					{
						//pass in table and condition tree to engine
						//return nothing
						string* tableName = (string*)(childTableName->getValue());
						Table* deleteTable = DBMS->findTable(*tableName);
						ConditionTree* condTree = (ConditionTree*)(childCondTree->getValue());
						DBMS->deleteFrom(deleteTable, *condTree);
						return NULL;
					}
				}
				throw("Wrong types in DELETE");
			}

			//if the sql input is an update command
			if (*value == UPDATE)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childValuePairs = (*(root->getChildren()))[1];
				EvaluationTree::Node* childCondTree = (*(root->getChildren()))[2];

				//if the children are of the correct types
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childValuePairs->getType() == ATTRIBUTE_VALUE_PAIR_LIST)
					{
						if (childCondTree->getType() == CONDITION_TREE)
						{
							//pass in table, values, and condition tree into engine
							//return nothing
							string* tableName = (string*)(childTableName->getValue());
							Table* updateTable = DBMS->findTable(*tableName);
							vector<tuple<string, string>>* values = (vector<tuple<string, string>>*)(childValuePairs->getValue());
							ConditionTree* condTree = (ConditionTree*)(childCondTree->getValue());
							DBMS->update(updateTable, *values, *condTree);
							return NULL;
						}
					}
				}
				throw("Wrong types in UPDATE");
			}
		}
	}

	catch (const char* error)
	{
		cout << error;
		return NULL;
	}
}
