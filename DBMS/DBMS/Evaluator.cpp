#pragma once

#include "Evaluator.h"
#include "EvaluationTree.h"

Evaluator::Evaluator(Engine* dbms) : DBMS(dbms)
{
	views = map<string, Table*>();
}

Table* Evaluator::Evaluate(EvaluationTree* tree)
{
	try {
		EvaluationTree::Node* root = tree->getRoot();
		if (root->getType() == QUERY){
			EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
			EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];

			if (leftChild->getType() == RELATION_NAME)
			{
				if (rightChild->getType() == EXPR)
				{
					EvaluationTree expressionTree = EvaluationTree(rightChild);
					Table* expressionTable = Evaluate(&expressionTree);
					string* value = (string*)(leftChild->getValue());
					views.insert(make_pair(*value, expressionTable));
					return NULL;
				}
			}
			throw("Wrong QUERY types");
		}

		if (root->getType() == EXPR)
		{
			string* value = (string*)(root->getValue());
			if (*value == SELECTION_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() == CONDITION_TREE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
						EvaluationTree expressionTree = EvaluationTree(rightChild);
						Table* expressionTable = Evaluate(&expressionTree);
						if (expressionTable != NULL){
							ConditionTree* condTree = (ConditionTree*)(leftChild->getValue());
							return DBMS->selection(expressionTable, *condTree);
						}
					}
				}
				throw("Wrong types in selection");
			}

			if (*value == PROJECTION_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() == ATTRIBUTE_LIST)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
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

			if (*value == RENAMING_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() != ATTRIBUTE_LIST)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
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

			if (*value == UNION_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() == PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
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

			if (*value == DIFFERENCE_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() == PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
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

			if (*value == PRODUCT_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() == PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
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

			if (*value == JOIN_EXPR)
			{
				EvaluationTree::Node* leftChild = (*(root->getChildren()))[0];
				EvaluationTree::Node* rightChild = (*(root->getChildren()))[1];
				if (leftChild->getType() == PARSE_FAILURE)
				{
					if (rightChild->getType() != PARSE_FAILURE)
					{
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

		if (root->getType() == RELATION_NAME){
			string* tableName = (string*)(root->getValue());
			auto mapIter = views.find(*tableName);
			if (mapIter != views.cend())
			{
				return mapIter->second;
			}

			return DBMS->findTable(*tableName);

			throw("relation name not valid");
		}

		if (root->getType() == COMMAND_OPERATOR)
		{
			string* value = (string*)(root->getValue());
			if (*value == OPEN)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];
				if (child->getType() == RELATION_NAME)
				{
					EvaluationTree expressionTree = EvaluationTree(child);
					Table* expressionTable = Evaluate(&expressionTree);
					if (expressionTable != NULL)
					{
						vector<string> queries = DBMS->openFile(expressionTable->getTableName());
						//WHAT NOW??
					}
				}
				throw("Wrong values in OPEN");
			}

			if (*value == WRITE)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];
				if (child->getType() == RELATION_NAME)
				{
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

			if (*value == CLOSE)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];
				if (child->getType() == RELATION_NAME)
				{
					EvaluationTree expressionTree = EvaluationTree(child);
					Table* expressionTable = Evaluate(&expressionTree);
					if (expressionTable != NULL)
					{
						DBMS->closeFile(expressionTable);
						return NULL;
					}
				}
				throw("Wrong values in CLOSE");
			}

			if (*value == EXIT)
			{
				//EXIT COMMAND???
			}

			if (*value == SHOW)
			{
				EvaluationTree::Node* child = (*(root->getChildren()))[0];
				if (child->getType() == RELATION_NAME)
				{
					EvaluationTree expressionTree = EvaluationTree(child);
					Table* expressionTable = Evaluate(&expressionTree);
					if (expressionTable != NULL)
					{
						DBMS->show(expressionTable);
						return NULL;
					}
				}
				throw("Wrong values in SHOW");
			}

			if (*value == CREATE_TABLE)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childColumns = (*(root->getChildren()))[1];
				EvaluationTree::Node* childKeys = (*(root->getChildren()))[2];
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childColumns->getType() == ATTRIBUTE_TYPE_PAIR_LIST)
					{
						if (childKeys->getType() == ATTRIBUTE_LIST)
						{
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
							DBMS->createTable(*tableName, *keys, columnTypes, columnNames);
							return NULL;
						}
					}
				}
				throw("Wrong types in CREATE");
			}

			if (*value == INSERT)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childLiteralList = (*(root->getChildren()))[1];
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childLiteralList->getType() == LITERAL_LIST)
					{
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
						DBMS->insertInto(insertTable, literalValues, literalTypes);
						return NULL;
					}
				}
				throw("Wrong types in INSERT");
			}

			if (*value == DELETE)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childCondTree = (*(root->getChildren()))[1];
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childCondTree->getType() == CONDITION_TREE)
					{
						string* tableName = (string*)(childTableName->getValue());
						Table* deleteTable = DBMS->findTable(*tableName);
						ConditionTree* condTree = (ConditionTree*)(childCondTree->getValue());
						DBMS->deleteFrom(deleteTable, *condTree);
						return NULL;
					}
				}
				throw("Wrong types in DELETE");
			}

			if (*value == UPDATE)
			{
				EvaluationTree::Node* childTableName = (*(root->getChildren()))[0];
				EvaluationTree::Node* childValuePairs = (*(root->getChildren()))[1];
				EvaluationTree::Node* childCondTree = (*(root->getChildren()))[2];
				if (childTableName->getType() == RELATION_NAME)
				{
					if (childValuePairs->getType() == ATTRIBUTE_VALUE_PAIR_LIST)
					{
						if (childCondTree->getType() == CONDITION_TREE)
						{
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
	}
}