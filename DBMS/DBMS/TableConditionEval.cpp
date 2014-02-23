#include <iostream>
#include "Table.h"
#include "Lexer.h"
#include "EvaluationTree.h"
#include "ConditionTree.h"

using namespace std;

typedef ConditionTree::Node Node;



//Will return TRUE or FALSE
//Unless trees formated incorectly
string Table::EvalConditionTree(ConditionTree* tree){

	tuple<string, string> result = NodeEval(tree->getRoot());

	string value = get<1>(result);
	return value;
}


//tuple< type , value > //NEED TO FIX
tuple<string, string> Table::NodeEval(ConditionTree::Node* n){


	string type = n->getType();
	string value = n->getValue();
	if (type == STRING_LITERAL || type == INT_LITERAL)
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
		if (value == EQUALS)
		{
			vector< Node* > children = n->getChildern();
			// test equality of the node's children
			if (get<1>(NodeEval(children[0])) == get<1>(NodeEval(children[1])))
				return make_tuple(STRING_LITERAL, TRUE);
			else
				return make_tuple(STRING_LITERAL, FALSE);
		}
		else if (value == NOT_EQUAL)
		{
			vector< Node* > children = n->getChildern();
			// test inequality of the node's children
			if (get<1>(NodeEval(children[0])) == get<1>(NodeEval(children[1])))
				return make_tuple(STRING_LITERAL, FALSE);
			else
				return make_tuple(STRING_LITERAL, TRUE);
		}
		else if (value == LESS_THAN)
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
			// ensure comparison can be done
			if (leftType != rightType)
			{
				return make_tuple(PARSE_FAILURE, "_TYPE_MISMATCH");
			}
			// in the case of a string
			else if (leftType == STRING_LITERAL)
			{
				if (leftValue == rightValue)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// in the case of an integer
			else if (leftType == INT_LITERAL)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == -1)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// something went wrong, return failure
			else return make_tuple(PARSE_FAILURE, UNKNOWN);
		}
		else if (value == GREATER_THAN)
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
			//ensure comparison can be done
			if (leftType != rightType)
			{
				return make_tuple(PARSE_FAILURE, "_TYPE_MISMATCH");
			}
			// in the case of a string
			else if (leftType == STRING_LITERAL)
			{
				if (leftValue == rightValue)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// in the case of an integer
			else if (leftType == INT_LITERAL)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == 1)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// something went wrong, return failure
			else return make_tuple(PARSE_FAILURE, UNKNOWN);
		}
		else if (value == LESS_EQUAL)
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
			// ensure comparison can be done
			if (leftType != rightType)
			{
				return make_tuple(PARSE_FAILURE, "_TYPE_MISMATCH");
			}
			// in the case of a string
			else if (leftType == STRING_LITERAL)
			{
				if (leftValue == rightValue)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// in the case of an integer
			else if (leftType == INT_LITERAL)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == -1 || comparison == 0)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// something went wrong, return failure
			else return make_tuple(PARSE_FAILURE, UNKNOWN);
		}
		else if (value == GREATER_EQUAL)
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
			// ensure comparison can be done
			if (leftType != rightType)
			{
				return make_tuple(PARSE_FAILURE, "_TYPE_MISMATCH");
			}
			// in the case of a string
			else if (leftType == STRING_LITERAL)
			{
				if (leftValue == rightValue)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// in the case of an integer
			else if (leftType == INT_LITERAL)
			{
				int comparison = compareStringInts(leftValue, rightValue);
				if (comparison == 1 || comparison == 0)
					return make_tuple(STRING_LITERAL, TRUE);
				else
					return make_tuple(STRING_LITERAL, FALSE);
			}
			// something went wrong, return failure
			else return make_tuple(PARSE_FAILURE, UNKNOWN);
		}
		else if (value == AND)
		{
			bool  result = true;
			vector<Node*> children = n->getChildern();

			// examine all children
			for (int i = 0; i < children.size(); i++)
			{
				tuple<string, string> Result = NodeEval(children[i]);
				string Type = get<0>(Result);
				string Value = get<1>(Result);

				// if any have false value, the result is false
				if (Value == FALSE)
					result = false;
			}

			// return appropriate value based on value of result
			if (result)
				return make_tuple(STRING_LITERAL, TRUE);
			else
				return make_tuple(STRING_LITERAL, FALSE);

		}
		else if (value == OR)
		{
			bool  result = false;
			vector<Node*> children = n->getChildern();

			// examine all children
			for (int i = 0; i < children.size(); i++)
			{
				tuple<string, string> Result = NodeEval(children[i]);
				string Type = get<0>(Result);
				string Value = get<1>(Result);

				// if any have true value, the result is true
				if (Value == TRUE)
					result = true;
			}

			// return appropriate value based on value of result
			if (result)
				return make_tuple(STRING_LITERAL, TRUE);
			else
				return make_tuple(STRING_LITERAL, FALSE);
		}
	}
		else if (type == VARIABLE)
		{
			Attribute* attribute = getVariable(value);
			string newType;
			string newValue;
			newValue = attribute->getValue();
			
			// in the case of an integer
			if (attribute->getType() == INT_LITERAL)
			{
				newType = INT_LITERAL;
			}
			// in the case of a string
			else if (attribute->getType() == STRING_LITERAL)
			{
				newType = STRING_LITERAL;
			}
			// something went wrong, assign failure
			else
			{
				newValue = "INVALID Varible Type";
				newType = PARSE_FAILURE;
			}
			return make_tuple(newType, newValue);
		}
		else return make_tuple(PARSE_FAILURE, UNKNOWN);
}


// compare integers that are stored as string types
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

