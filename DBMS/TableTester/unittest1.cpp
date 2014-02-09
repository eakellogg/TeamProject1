#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Engine.h"
#include "Table.h"
#include "Attribute.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TableTester
{
	TEST_CLASS(UnitTest1)
	{
	public:

		// create information to put into table to prepare testing
		Attribute* namea = new Attribute("string", "Zach Brown");
		Attribute* nameb = new Attribute("string", "Jacob Zerr");
		Attribute* namec = new Attribute("string", "Victoria Elliott");

		Attribute* schoola = new Attribute("string", "Texas A&M");
		Attribute* schoolb = new Attribute("string", "Kansas University");
		Attribute* schoolc = new Attribute("string", "Wake Forest");

		Attribute* agea = new Attribute("int", "20");
		Attribute* ageb = new Attribute("int", "75");
		Attribute* agec = new Attribute("int", "18");

		Attribute* citya = new Attribute("string", "College Station");
		Attribute* cityb = new Attribute("string", "San Antonio");
		Attribute* cityc = new Attribute("string", "Frederick");

		Attribute* statea = new Attribute("string", "Texas");
		Attribute* stateb = new Attribute("string", "Maryland");
		Attribute* statec = new Attribute("string", "Missouri");

		vector<string> columnTypesA = vector<string>{"string", "string", "int"};
		vector<string> columnTypesB = vector<string>{"string", "string", "string"};
		vector<string> badColumnTypes = vector<string>{"int", "int", "int"};

		vector<string> columnTitlesA = vector<string>{"name", "school", "age"};
		vector<string> columnTitlesB = vector<string>{"name", "school", "state"};

		vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
		vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
		vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};

		//Table* tbla = new Table("TableA", "name", columnTypesA, columnTitlesA);
		//Table* tblb = new Table("TableB", "name", columnTypesB, columnTitlesB);

		Engine testEngine = Engine();

//************************************************************************************************************

//************************************************************************************************************

		TEST_METHOD(Creating_Table)
		{
			// should throw an error because badKey is not in the list of given column names
			try{
				testEngine.createTable("tableName", "badKey", columnTypesA, columnTitlesA);
			}
			catch (const char* error) {
				// check error message equality
				Assert::AreEqual(error, "key name does not match any column, table not created");
			}

			// should be successful
			string tableName = "tableName";
			testEngine.createTable(tableName, "name", columnTypesA, columnTitlesA);

			// check name equality
			Assert::AreEqual(tableName, testEngine.getTables()[0]->getTableName());

			// check row type equality
			for (int i = 0; i < testEngine.getTables()[0]->getColumnTypes().size(); i++) {
				Assert::AreEqual(columnTypesA[i], testEngine.getTables()[0]->getColumnTypes()[i]);
			}

			// check row title equality
			for (int i = 0; i < testEngine.getTables()[0]->getColumnTitles().size(); i++) {
				Assert::AreEqual(columnTitlesA[i], testEngine.getTables()[0]->getColumnTitles()[i]);
			}
		}

//************************************************************************************************************

//************************************************************************************************************

		TEST_METHOD(Dropping_Table)
		{
			// verify number of tables
			Assert::IsTrue(testEngine.getTables().size() == 0);

			testEngine.createTable("tableName", "name", columnTypesA, columnTitlesA);

			// verify table was added correctly
			Assert::IsTrue(testEngine.getTables().size() == 1);

			// should throw an error because badTableName is not the name of any existing table
			try {
				testEngine.dropTable("badTableName");
			}
			catch (const char* error) {
				// check error message equality
				Assert::AreEqual(error, "table does not exist");
			}

			testEngine.dropTable("tableName");

			// verify that number of tables is one less
			Assert::IsTrue(testEngine.getTables().size() == 0);
		}

//************************************************************************************************************

//************************************************************************************************************
		
		TEST_METHOD(Insert_Row_Test){
			// verify number of tables
			testEngine.createTable("tableName", "name", columnTypesA, columnTitlesA);

			Assert::IsTrue(testEngine.getTables().size() == 1); // one table
			Assert::IsTrue(testEngine.getTables()[0]->getData().size() == 0); // table has no rows

			// should throw an error because badTableName is not the name of any existing table
			try {
				testEngine.insertInto("badTableName", student1, columnTypesA);
			}
			catch (const char* error) {
				// check error message equality
				Assert::AreEqual(error, "table does not exist");
			}

			// should throw an error because column types do not match
			try {
				testEngine.insertInto("tableName", student1, columnTypesB);
			}
			catch (const char* error) {
				// check error message equality
				Assert::AreEqual(error, "types do not match");
			}

			testEngine.insertInto("tableName", student1, columnTypesA);
			map<string, vector<Attribute*>> addedAttributes = testEngine.getTables()[0]->getData();

			Assert::IsTrue(addedAttributes.size() == 1); // table has one row after insertion

			// check each row of the table
			for (map<string, vector<Attribute*>>::iterator i = addedAttributes.begin(); i != addedAttributes.end(); i++) {
				// check all attribute's type and value equality in the each row
				for (int j = 0; j < i->second.size(); j++) {
					Assert::AreEqual(i->second[j]->getType(), student1[j]->getType());
					Assert::AreEqual(i->second[j]->getValue(), student1[j]->getValue());
				}
			}
		}

//************************************************************************************************************

//************************************************************************************************************

		TEST_METHOD(Cross_Product_Test){
			// verify number of tables
			testEngine.createTable("tableName", "name", columnTypesA, columnTitlesA);
		}

//************************************************************************************************************

//************************************************************************************************************

		TEST_METHOD(Natural_Join_Test) {
			// create information to put into table to prepare testing
			Engine engine = Engine();
			

			Table* tbla = new Table("testTableA", "name", columnTypesA, columnTitlesA);
			Table* tblb = new Table("testTableA", "name", columnTypesB, columnTitlesB);
			//Table* tblc = engine.naturalJoin(tbla, tblb);
		}

//************************************************************************************************************

//************************************************************************************************************

		TEST_METHOD(Set_Union_Test){
			// set_union_test
		}

//************************************************************************************************************

//************************************************************************************************************

		TEST_METHOD(Set_Difference_Test){
			// set_difference_test
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(Attribute_Test)
		{
			string type = "type";
			string value = "value";
			string newvalue = "newvalue";

			// test getting type and value
			Attribute* attr = new Attribute(type, value);
			Assert::AreEqual(attr->getType(), type);
			Assert::AreEqual(attr->getValue(), value);

			//************************************************************************************************************

			// test setting value
			attr->setValue(newvalue);
			Assert::AreEqual(attr->getValue(), newvalue);
		}

		TEST_METHOD(Table_Test)
		{
			// create information to put into table to prepare testing
			Attribute* namea = new Attribute("string", "Zach Brown");
			Attribute* nameb = new Attribute("string", "Jacob Zerr");
			Attribute* namec = new Attribute("string", "Victoria Elliott");

			Attribute* schoola = new Attribute("string", "Texas A&M");
			Attribute* schoolb = new Attribute("string", "Kansas University");
			Attribute* schoolc = new Attribute("string", "Wake Forest");

			Attribute* agea = new Attribute("int", "20");
			Attribute* ageb = new Attribute("int", "75");
			Attribute* agec = new Attribute("int", "18");

			vector<string> columnTypes = vector<string>{"string", "string", "int"};
			vector<string> badRowTypes = vector<string>{"string", "string", "string"};
			vector<string> columnTitles = vector<string>{"name", "school", "age"};

			vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
			vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
			vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};

			Table* tbl = new Table("testTable", "name",  columnTypes, columnTitles);

			//************************************************************************************************************

			// test adding rows
			try {
				tbl->addRow(student1, columnTypes);
				tbl->addRow(student2, columnTypes);
				tbl->addRow(student3, badRowTypes); // should throw an error b/c of improper row types
			}
			catch (const char* error) {
				Assert::AreEqual(error, "types do not match"); // verify error is thrown
			}

			//************************************************************************************************************

			// test deleting rows
			tbl->deleteRow(student1[0]->getValue());
			Assert::IsTrue(tbl->getData().size() == 1); // added two students, deleted one; make sure size is now 1

			//************************************************************************************************************

			// test accessing rows
			try {
				tbl->getRow(student2[0]->getValue());
				tbl->getRow(student1[0]->getValue()); // should throw an error b/c student1 was deleted
			}
			catch (const char* error) {
				Assert::AreEqual(error, "key does not exist"); // verify error is thrown
			}

			//************************************************************************************************************

			// test accessing items
			try {
				tbl->getItem(student1[0]->getValue(), "name"); // should throw error b/c student1 was deleted
			}
			catch (const char* error) {
				Assert::AreEqual(error, "key does not exist"); // verify error is thrown
			}
			try {
				tbl->getItem(student2[0]->getValue(), "major"); // should throw error b/c "major" is not a column types
			}
			catch (const char* error) {
				Assert::AreEqual(error, "column does not exist"); // verify error is thrown
			}
			string item = tbl->getItem(student2[0]->getValue(), "name")->getValue();
			Assert::AreEqual(item, student2[0]->getValue());

			//************************************************************************************************************

			// test accessing a variable; current row is still student2 from above
			try {
				tbl->getVariable("major"); // should throw error b/c "major" is not column type
			}
			catch (const char* error) {
				Assert::AreEqual(error, "variable does not exist"); // verify error is thrown
			}

			Assert::IsTrue(atoi(tbl->getVariable("age")->getValue().c_str()) == atoi(student2[2]->getValue().c_str()));

		}

		TEST_METHOD(Engine_Test){
			// create information to put into table to prepare testing
			Attribute* namea = new Attribute("string", "Zach Brown");
			Attribute* nameb = new Attribute("string", "Jacob Zerr");
			Attribute* namec = new Attribute("string", "Victoria Elliott");

			Attribute* schoola = new Attribute("string", "Texas A&M");
			Attribute* schoolb = new Attribute("string", "Kansas University");
			Attribute* schoolc = new Attribute("string", "Wake Forest");

			Attribute* agea = new Attribute("int", "20");
			Attribute* ageb = new Attribute("int", "75");
			Attribute* agec = new Attribute("int", "18");

			vector<string> columnTypes = vector<string>{"string", "string", "int"};
			vector<string> badRowTypes = vector<string>{"string", "string", "string"};
			vector<string> columnTitles = vector<string>{"name", "school", "age"};

			vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
			vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
			vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};

			Engine engine = Engine();

			//************************************************************************************************************

			// test adding tables
			engine.createTable("students", "name" ,  columnTypes, columnTitles);
			engine.createTable("people", "name", columnTypes, columnTitles);
			Assert::IsTrue(engine.getTables().size() == 2);

			//************************************************************************************************************

			// test deleting tables
			try {
				engine.dropTable("children"); // should throw error b/c no table with that name
			}
			catch (const char* error) {
				Assert::AreEqual(error, "table does not exist"); // verify error is thrown
			}
			engine.dropTable("people");
			Assert::IsTrue(engine.getTables().size() == 1); // added to tables, deleted one; make sure size is now 1

			//************************************************************************************************************

			// test insert into a table
			try {
				engine.insertInto("children",student1, columnTypes); // should throw error b/c no table with that name
			}
			catch (const char* error) {
				Assert::AreEqual(error, "table does not exist"); // verify error is thrown
			}

			engine.insertInto("students",student1, columnTypes);
			engine.insertInto("students",student2, columnTypes);
			Assert::IsTrue(engine.getTables()[0]->getData().size() == 2); // added two students, make sure size is now 2
		}

		TEST_METHOD(Natural_Join_Test) {
			// create information to put into table to prepare testing
			Engine engine = Engine();
			vector<string> columnTypesA = vector<string>{"string", "string", "string"};
			vector<string> columnTitlesA = vector<string>{"name", "school", "state"};
			vector<string> columnTypesB = vector<string>{"string", "string", "int"};
			vector<string> columnTitlesB = vector<string>{"name", "school", "age"};

			Table* tbla = new Table("testTableA", "name",  columnTypesA, columnTitlesA);
			Table* tblb = new Table("testTableA", "name" ,columnTypesB, columnTitlesB);
			//Table* tblc = engine.naturalJoin(tbla, tblb);
		}

	};
	TEST_CLASS(EvalTest)
	{
	public:

		TEST_METHOD(Test_Equality_String)
		{
			//Current checks the results of eval on a simple two operand tree with equailty

			ConditionTree t(EQUAL, OPERATOR);
			ConditionTree::Node* n = t.getRoot();

			n->setLeftChild("Hello", LITERAL_STRING);
			n->setRightChild("Hello", LITERAL_STRING);

			Table* table = new Table("DUMMY", "Name" , vector<string>{ "Name" }, vector<string>{ "STRING" });
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
		