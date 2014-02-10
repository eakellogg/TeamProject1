#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EvalTest
{

	TEST_CLASS(Engine_Query_Methods_Simple)
	{
	public:
		TEST_METHOD(Update) {

			vector<string> columnTypes;
			columnTypes.push_back(STRING_TYPE);
			vector<string> columnNames;
			columnNames.push_back("Name");

			Attribute* a = new Attribute(STRING_TYPE, "BOB");
			vector<Attribute*> row;
			row.push_back(a);

			Engine engine;
			engine.createTable("TestTable", "Name", columnTypes, columnNames);
			engine.insertInto("TestTable", row, columnTypes);

			vector< tuple<string, string> > namevarpairs;
			namevarpairs.push_back(make_tuple("Name", "Emily"));

			ConditionTree t(EQUAL, OPERATOR);
			ConditionTree::Node* n = t.getRoot();

			n->setLeftChild("Name", VARIABLE);
			n->setRightChild("BOB", LITERAL_STRING);

			engine.update("TestTable", namevarpairs, t);

			Table* table = engine.findTable("TestTable");

			map< string, vector<Attribute*> > data = table->getData();
			map< string, vector<Attribute*> >::iterator it = data.begin();

			vector< Attribute* > ats = it->second;

			Assert::AreEqual(ats[0]->getValue().c_str(), "Emily");
		}
		TEST_METHOD(Test_Selection)
		{
			//TODO improve!
			vector<string> columnTypes;
			columnTypes.push_back(STRING_TYPE);
			vector<string> columnNames;
			columnNames.push_back("Name");

			Attribute* a = new Attribute(STRING_TYPE, "BOB");
			vector<Attribute*> row;
			row.push_back(a);

			Engine engine;
			engine.createTable("TestTable", "Name", columnTypes, columnNames);
			engine.insertInto("TestTable",  row, columnTypes);

			vector< tuple<string, string> > namevarpairs;
			namevarpairs.push_back(make_tuple("Name", "BOB"));

			ConditionTree t(EQUAL, OPERATOR);
			ConditionTree::Node* n = t.getRoot();

			n->setLeftChild("Name", VARIABLE);
			n->setRightChild("BOB", LITERAL_STRING);

			Table* newTable = engine.selection("TestTable", t);


			map< string, vector<Attribute*> > data = newTable->getData();
			map< string, vector<Attribute*> >::iterator it = data.begin();

			vector< Attribute* > ats = it->second;

			Assert::AreEqual(ats[0]->getValue().c_str(), "BOB");
		}
		TEST_METHOD(Delete) {

			vector<string> columnTypes;
			columnTypes.push_back(STRING_TYPE);
			vector<string> columnNames;
			columnNames.push_back("Name");

			Attribute* a = new Attribute(STRING_TYPE, "BOB");
			vector<Attribute*> row;
			row.push_back(a);

			Engine engine;
			engine.createTable("TestTable", "Name", columnTypes, columnNames);
			engine.insertInto("TestTable", row, columnTypes);


			ConditionTree t(EQUAL, OPERATOR);
			ConditionTree::Node* n = t.getRoot();

			n->setLeftChild("Name", VARIABLE);
			n->setRightChild("BOB", LITERAL_STRING);

			engine.deleteFrom("TestTable", t);

			Table* table = engine.findTable("TestTable");

			map< string, vector<Attribute*> > data = table->getData();
			map< string, vector<Attribute*> >::iterator it = data.begin();

			bool result = false;
			if (it == data.end())
				result = true;
			Assert::AreEqual(result, true);
		}
	};
};