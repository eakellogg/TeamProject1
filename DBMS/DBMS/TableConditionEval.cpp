#include <iostream>
#include "Table.h"

typedef ConditionTree::Node Node;
using namespace std;



//Will return TRUE or FALSE
//Unless trees formated incorectly
string Table::EvalConditionTree(ConditionTree* tree){

	tuple<string, string> result = NodeEval(tree->getRoot());
	return get<1>(result);
}

//tuple< type , value > //NEED TO FIX
tuple<string, string> Table::NodeEval(ConditionTree::Node* n){

	string type = n->getType();
	string value = n->getValue();

	if (type == LITERAL_STRING || type == LITERAL_INT)
	{
		return make_tuple(type, value);
	}
	else if (type == OPERATOR)
	{
		/*
		const std::string EQUAL = "=";
		const std::string LESS = "<";
		const std::string GREATER = ">";
		const std::string LESSEQUAL = "<=";
		const std::string GREATEREQUAL = ">=";
		const std::string AND = "&&";
		const std::string OR = "||";
		const std::string NOT = "!";
		*/
		if (value == EQUAL)
		{
			vector< Node* > children = n->getChildern();
			if (get<1>(NodeEval(children[0])) == get<1>(NodeEval(children[1])))
				return make_tuple(LITERAL_STRING, TRUE);
			else
				return make_tuple(LITERAL_STRING, FALSE);
		}

		else if (value == LESS)
		{
			vector < Node* > children = n->getChildern();
			ConditionTree::Node* leftChild = children[0];
			ConditionTree::Node* rightChild = children[1];
			tuple<string, string> leftResult = NodeEval(leftChild);
			tuple<string, string> rightResult = NodeEval(rightChild);
			string leftType = get<0>(leftResult);
			string rightType = get<0>(rightResult);
			string leftValue = get<1>(leftResult);
			string rightValue = get<1>(rightResult);

			if (leftType != rightType)
			{
				return make_tuple(FAILURE, "_TYPE_MISMATCH");
			}
			else if (leftType == LITERAL_STRING)
			{
				if (leftValue == rightValue)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else if (leftType == LITERAL_INT)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == -1)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else return make_tuple(FAILURE, UNKNOWN);
		}
		else if (value == GREATER)
		{
			vector < Node* > children = n->getChildern();
			ConditionTree::Node* leftChild = children[0];
			ConditionTree::Node* rightChild = children[1];
			tuple<string, string> leftResult = NodeEval(leftChild);
			tuple<string, string> rightResult = NodeEval(rightChild);
			string leftType = get<0>(leftResult);
			string rightType = get<0>(rightResult);
			string leftValue = get<1>(leftResult);
			string rightValue = get<1>(rightResult);

			if (leftType != rightType)
			{
				return make_tuple(FAILURE, "_TYPE_MISMATCH");
			}
			else if (leftType == LITERAL_STRING)
			{
				if (leftValue == rightValue)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else if (leftType == LITERAL_INT)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == 1)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else return make_tuple(FAILURE, UNKNOWN);
		}
		else if (value == LESSEQUAL)
		{
			vector < Node* > children = n->getChildern();
			ConditionTree::Node* leftChild = children[0];
			ConditionTree::Node* rightChild = children[1];
			tuple<string, string> leftResult = NodeEval(leftChild);
			tuple<string, string> rightResult = NodeEval(rightChild);
			string leftType = get<0>(leftResult);
			string rightType = get<0>(rightResult);
			string leftValue = get<1>(leftResult);
			string rightValue = get<1>(rightResult);

			if (leftType != rightType)
			{
				return make_tuple(FAILURE, "_TYPE_MISMATCH");
			}
			else if (leftType == LITERAL_STRING)
			{
				if (leftValue == rightValue)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else if (leftType == LITERAL_INT)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == -1 || comparison == 0)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else return make_tuple(FAILURE, UNKNOWN);
		}
		else if (value == GREATEREQUAL)
		{
			vector < Node* > children = n->getChildern();
			ConditionTree::Node* leftChild = children[0];
			ConditionTree::Node* rightChild = children[1];
			tuple<string, string> leftResult = NodeEval(leftChild);
			tuple<string, string> rightResult = NodeEval(rightChild);
			string leftType = get<0>(leftResult);
			string rightType = get<0>(rightResult);
			string leftValue = get<1>(leftResult);
			string rightValue = get<1>(rightResult);

			if (leftType != rightType)
			{
				return make_tuple(FAILURE, "_TYPE_MISMATCH");
			}
			else if (leftType == LITERAL_STRING)
			{
				if (leftValue == rightValue)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else if (leftType == LITERAL_INT)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == 1 || comparison == 0)
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else return make_tuple(FAILURE, UNKNOWN);
		}
		else if (value == AND)
		{
			bool  result = true;
			vector<Node*> children = n->getChildern();

			for (int i = 0; i < children.size(); i++)
			{
				tuple<string, string> Result = NodeEval(children[i]);
				string Type = get<0>(Result);
				string Value = get<1>(Result);

				if (Value == FALSE)
					result = false;
			}

			if (result)
				return make_tuple(LITERAL_STRING, TRUE);
			else
				return make_tuple(LITERAL_STRING, FALSE);

		}
		else if (value == OR)
		{
			bool  result = false;
			vector<Node*> children = n->getChildern();

			for (int i = 0; i < children.size(); i++)
			{
				tuple<string, string> Result = NodeEval(children[i]);
				string Type = get<0>(Result);
				string Value = get<1>(Result);

				if (Value == TRUE)
					result = true;
			}

			if (result)
				return make_tuple(LITERAL_STRING, TRUE);
			else
				return make_tuple(LITERAL_STRING, FALSE);
		}
		else if (type == VARIABLE)
		{
			Attribute* attribute = getVariable(value);

			string newType;
			string newValue;
			newValue = attribute->getValue();
			if (attribute->getType() == INT_TYPE)
			{
				newType = LITERAL_INT;
			}
			else if (attribute->getType() == STRING_TYPE)
			{
				newType = LITERAL_STRING;
			}
			else
			{
				newValue = "INVALID Varible Type";
				newType = FAILURE;
			}
			return make_tuple(newType, newValue);

		}
		else return make_tuple(FAILURE, UNKNOWN);
	}
}


int Table::compareStringInts(string lv, string rv)
{
	int li = atoi(lv.c_str());
	int ri = atoi(rv.c_str());
	if (li > ri)
		return 1;
	else
	if (li < ri)
		return -1;
	else
		return 0;
}
