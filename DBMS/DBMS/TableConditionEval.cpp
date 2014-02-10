
#include <iostream>
#include "Table.h"

using namespace std;



//Will return TRUE or FALSE
//Unless trees formated incorectly
string Table::EvalConditionTree(ConditionTree* tree){

	tuple<string, string> result = NodeEval(tree->getRoot());
	return get<1>(result);
}

//tuple< type , value >
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
			cout << get<1>(NodeEval(n->getLeftChild()));
			cout << get<1>(NodeEval(n->getRightChild())) << endl;
			if (get<1>(NodeEval(n->getLeftChild())) == get<1>(NodeEval(n->getRightChild())))
				return make_tuple(LITERAL_STRING, TRUE);
			else
				return make_tuple(LITERAL_STRING, FALSE);
		}

		else if (value == LESS)
		{
			ConditionTree::Node* leftChild = n->getLeftChild();
			ConditionTree::Node* rightChild = n->getRightChild();
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
			ConditionTree::Node* leftChild = n->getLeftChild();
			ConditionTree::Node* rightChild = n->getRightChild();
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
			ConditionTree::Node* leftChild = n->getLeftChild();
			ConditionTree::Node* rightChild = n->getRightChild();
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
		else if ( value == GREATEREQUAL)
		{
			ConditionTree::Node* leftChild = n->getLeftChild();
			ConditionTree::Node* rightChild = n->getRightChild();
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
		else if ( value == AND)
		{
			ConditionTree::Node* leftChild = n->getLeftChild();
			ConditionTree::Node* rightChild = n->getRightChild();
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
			else if ((leftValue == TRUE || leftValue == FALSE) && ( rightValue == TRUE || leftValue == FALSE ))
			{
				if ((leftValue == TRUE) && (rightValue == TRUE) )
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else if (leftType == LITERAL_INT)
			{
				return make_tuple(FAILURE, "INT invalid operand for &&");
			}
			else return make_tuple(FAILURE, "Invalid operand for &&");
		}
		else if (value == OR)
		{
			ConditionTree::Node* leftChild = n->getLeftChild();
			ConditionTree::Node* rightChild = n->getRightChild();
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
			else if ((leftValue == TRUE || leftValue == FALSE) && (rightValue == TRUE || leftValue == FALSE))
			{
				if ((leftValue == TRUE) || (rightValue == TRUE))
					return make_tuple(LITERAL_STRING, TRUE);
				else
					return make_tuple(LITERAL_STRING, FALSE);
			}
			else if (leftType == LITERAL_INT)
			{
				return make_tuple(FAILURE, "INT invalid operand for ||");
			}
			else return make_tuple(FAILURE, "Invalid operand for ||");
		}
		else if (value == NOT)
		{
			if (n->getRightChild() != NULL)
				return make_tuple(FAILURE, "NOT many only have one operand");
			ConditionTree::Node* leftChild = n->getLeftChild();
			tuple<string, string> leftResult = NodeEval(leftChild);
			string leftType = get<0>(leftResult);
			string leftValue = get<1>(leftResult);


			 if ((leftValue == TRUE || leftValue == FALSE))
			{
				if ((leftValue == TRUE) )
					return make_tuple(LITERAL_STRING, FALSE);
				else
					return make_tuple(LITERAL_STRING, TRUE);
			}
			else if (leftType == LITERAL_INT)
			{
				return make_tuple(FAILURE, "INT invalid operand for NOT");
			}
			else return make_tuple(FAILURE, "Invalid operand for NOT");
		}
		else return make_tuple(FAILURE, "Failed to match any operand");

	}
	else if ( type == VARIABLE)
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
		cout << "Evalutiona of variable returns " << newValue << endl;
		return make_tuple(newType, newValue);

	}
	else return make_tuple(FAILURE, UNKNOWN);
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