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
};
		