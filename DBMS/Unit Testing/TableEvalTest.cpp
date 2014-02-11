#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EvalTest
{

TEST_CLASS(SimpleEvalTests)
{
public:

	TEST_METHOD(Test_Equality_String)
	{
		//Current checks the results of eval on a simple two operand tree with equailty

		ConditionTree t(EQUAL, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("Hello", LITERAL_STRING);
		n->setRightChild("Hello", LITERAL_STRING);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setRightChild("Bye", LITERAL_STRING);
		result = table->EvalConditionTree(&t);
		Assert::AreNotEqual(TRUE.c_str(), result.c_str());

	}

	TEST_METHOD(Test_Less_Int)
	{

		ConditionTree t(LESS, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("5", LITERAL_INT);
		n->setRightChild("10", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("11", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());

	}

	TEST_METHOD(Test_Greater_Int)
	{

		ConditionTree t(GREATER, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("10", LITERAL_INT);
		n->setRightChild("5", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("4", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());

	}

	TEST_METHOD(Test_LessEqual_Int)
	{

		ConditionTree t(LESSEQUAL, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("5", LITERAL_INT);
		n->setRightChild("10", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("10", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("11", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());
	}

	TEST_METHOD(Test_GreaterEqual_Int)
	{

		ConditionTree t(GREATEREQUAL, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("10", LITERAL_INT);
		n->setRightChild("5", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("5", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("4", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());

	}

	TEST_METHOD(Test_AND)
	{

		ConditionTree t(AND, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("TRUE", LITERAL_INT);
		n->setRightChild("TRUE", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("FALSE", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());

		n->setLeftChild("FALSE", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());

	}

	TEST_METHOD(Test_OR)
	{

		ConditionTree t(OR, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("TRUE", LITERAL_INT);
		n->setRightChild("TRUE", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setLeftChild("FALSE", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(TRUE.c_str(), result.c_str());

		n->setRightChild("FALSE", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(FALSE.c_str(), result.c_str());

	}

	TEST_METHOD(Test_NOT)
	{

		ConditionTree t(NOT, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		n->setLeftChild("TRUE", LITERAL_INT);

		Table* table = new Table("DUMMY", "Name", vector<string>{ "Name" }, vector<string>{ "STRING" });
		string result = table->EvalConditionTree(&t);

		Assert::AreEqual(FALSE.c_str(), result.c_str());

		n->setLeftChild("FALSE", LITERAL_INT);

		result = table->EvalConditionTree(&t);
		Assert::AreEqual(TRUE.c_str(), result.c_str());
	}

};

};