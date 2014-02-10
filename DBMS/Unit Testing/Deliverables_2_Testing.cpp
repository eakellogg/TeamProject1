#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TableTester
{
	TEST_CLASS(Deliverables2_Testing)
	{
	public:
		// create information to put into table to prepare testing
		Attribute* namea = new Attribute("string", "Zach Brown");
		Attribute* nameb = new Attribute("string", "Jacob Zerr");
		Attribute* namec = new Attribute("string", "Victoria Elliott");
		Attribute* named = new Attribute("string", "Johnny Football");

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
		vector<string> columnTitlesB = vector<string>{"name", "city", "state"};
		vector<string> badColumnTitles = vector<string>{"weight", "height", "favorite number"};

		vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
		vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
		vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};

		vector<Attribute*> person1 = vector<Attribute*>{namea, citya, statea};
		vector<Attribute*> person2 = vector<Attribute*>{nameb, cityb, stateb};
		vector<Attribute*> person3 = vector<Attribute*>{named, cityc, statec};

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

			string tableName = "tableName";
			testEngine.createTable(tableName, "name", columnTypesA, columnTitlesA);

			// check name equality
			Assert::AreEqual(tableName, testEngine.getTables()[0]->getTableName());

			// check row type equality
			for (unsigned int i = 0; i < testEngine.getTables()[0]->getColumnTypes().size(); i++) {
				Assert::AreEqual(columnTypesA[i], testEngine.getTables()[0]->getColumnTypes()[i]);
			}

			// check row title equality
			for (unsigned int i = 0; i < testEngine.getTables()[0]->getColumnTitles().size(); i++) {
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

		TEST_METHOD(Insert_Into){
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
				for (unsigned int j = 0; j < i->second.size(); j++) {
					Assert::AreEqual(i->second[j]->getType(), student1[j]->getType());
					Assert::AreEqual(i->second[j]->getValue(), student1[j]->getValue());
				}
			}
		}

		//************************************************************************************************************

		//************************************************************************************************************

		TEST_METHOD(Projection)
		{
			vector<string> columnTypes;
			columnTypes.push_back(STRING_TYPE);
			columnTypes.push_back(INT_TYPE);
			vector<string> columnNames;
			columnNames.push_back("Name");
			columnNames.push_back("Age");
			
			Attribute* a = new Attribute(STRING_TYPE, "BOB");
			Attribute* b = new Attribute(INT_TYPE, "10");
			vector<Attribute*> row;
			row.push_back(a);
			row.push_back(b);

			Engine engine;
			engine.createTable("TestTable", "Name", columnTypes, columnNames);
			engine.insertInto("TestTable", row, columnTypes);
			



			// error occurs at this line
			Table* newTable = engine.projection("TestTable", vector<string>{"Age"});

			
			map< string, vector<Attribute*> > data = newTable->getData();
			map< string, vector<Attribute*> >::iterator it = data.begin();

			vector< Attribute* > ats = it->second;

			Assert::AreEqual(ats[0]->getValue().c_str(), "10");
		}

		//************************************************************************************************************

		//************************************************************************************************************

		TEST_METHOD(Cross_Product){
			testEngine.createTable("students", "name", columnTypesA, columnTitlesA);
			testEngine.createTable("people", "state", columnTypesB, columnTitlesB);

			testEngine.insertInto("students", student1, columnTypesA);
			testEngine.insertInto("students", student2, columnTypesA);

			testEngine.insertInto("people", person1, columnTypesB);
			testEngine.insertInto("people", person2, columnTypesB);

			Table* tbla = testEngine.getTables()[0];
			Table* tblb = testEngine.getTables()[1];
			Table* tblc = testEngine.crossProduct(tbla, tblb);

			// verify correct size of cross product table
			Assert::IsTrue(tblc->getData().size() == tbla->getData().size() * tblb->getData().size());

			// verify that new table has correctly merged column titles
			for (int i = 0; i < tbla->getColumnTitles().size(); i++) {
				Assert::AreEqual(tblc->getColumnTitles()[i], tbla->getColumnTitles()[i]);
			}
			for (int i = 0; i < tblb->getColumnTitles().size(); i++) {
				Assert::AreEqual(tblc->getColumnTitles()[i + tblb->getColumnTitles().size()], tblb->getColumnTitles()[i]);
			}
			Assert::AreEqual(tblc->getColumnTitles()[tblc->getColumnTitles().size() - 1], tbla->getTableName() + tblb->getTableName());

			// verify that new table has correctly merged column types
			for (int i = 0; i < tbla->getColumnTypes().size(); i++) {
				Assert::AreEqual(tblc->getColumnTypes()[i], tbla->getColumnTypes()[i]);
			}
			for (int i = 0; i < tblb->getColumnTitles().size(); i++) {
				Assert::AreEqual(tblc->getColumnTypes()[i + tblb->getColumnTypes().size()], tblb->getColumnTypes()[i]);
			}

			string identifierType = "int";
			Assert::AreEqual(tblc->getColumnTypes()[tblc->getColumnTypes().size() - 1], identifierType);

			// need to check new table and ensure equality where it's needed - hardcoded values are what is expected
			map<string, vector<Attribute*>> tblcData = tblc->getData();
			map<string, vector<Attribute*>>::iterator it = tblcData.begin();

			vector<Attribute*> rowa = it->second;
			Assert::IsTrue(rowa[0]->getValue() == "Jacob Zerr");
			Assert::IsTrue(rowa[1]->getValue() == "Kansas University");
			Assert::IsTrue(rowa[2]->getValue() == "75");
			Assert::IsTrue(rowa[3]->getValue() == "Jacob Zerr");
			Assert::IsTrue(rowa[4]->getValue() == "San Antonio");
			Assert::IsTrue(rowa[5]->getValue() == "Maryland");
			Assert::IsTrue(rowa[6]->getValue() == "0000000000");
			it++;

			vector<Attribute*> rowb = it->second;
			Assert::IsTrue(rowb[0]->getValue() == "Jacob Zerr");
			Assert::IsTrue(rowb[1]->getValue() == "Kansas University");
			Assert::IsTrue(rowb[2]->getValue() == "75");
			Assert::IsTrue(rowb[3]->getValue() == "Zach Brown");
			Assert::IsTrue(rowb[4]->getValue() == "College Station");
			Assert::IsTrue(rowb[5]->getValue() == "Texas");
			Assert::IsTrue(rowb[6]->getValue() == "0000000001");
			it++;

			vector<Attribute*> rowc = it->second;
			Assert::IsTrue(rowc[0]->getValue() == "Zach Brown");
			Assert::IsTrue(rowc[1]->getValue() == "Texas A&M");
			Assert::IsTrue(rowc[2]->getValue() == "20");
			Assert::IsTrue(rowc[3]->getValue() == "Jacob Zerr");
			Assert::IsTrue(rowc[4]->getValue() == "San Antonio");
			Assert::IsTrue(rowc[5]->getValue() == "Maryland");
			Assert::IsTrue(rowc[6]->getValue() == "0000000002");
			it++;

			vector<Attribute*> rowd = it->second;
			Assert::IsTrue(rowd[0]->getValue() == "Zach Brown");
			Assert::IsTrue(rowd[1]->getValue() == "Texas A&M");
			Assert::IsTrue(rowd[2]->getValue() == "20");
			Assert::IsTrue(rowd[3]->getValue() == "Zach Brown");
			Assert::IsTrue(rowd[4]->getValue() == "College Station");
			Assert::IsTrue(rowd[5]->getValue() == "Texas");
			Assert::IsTrue(rowd[6]->getValue() == "0000000003");
		}

		//************************************************************************************************************

		//************************************************************************************************************

		TEST_METHOD(Natural_Join) {
			testEngine.createTable("students", "name", columnTypesA, columnTitlesA);
			testEngine.createTable("people", "state", columnTypesB, columnTitlesB);
			testEngine.createTable("badTable", "weight", badColumnTypes, badColumnTitles);

			testEngine.insertInto("students", student1, columnTypesA);
			testEngine.insertInto("students", student2, columnTypesA);

			testEngine.insertInto("people", person1, columnTypesB);
			testEngine.insertInto("people", person2, columnTypesB);

			Table* tbla = testEngine.getTables()[0];
			Table* tblb = testEngine.getTables()[1];
			Table* tblc = testEngine.getTables()[2];

			try {
				Table* tbld = testEngine.naturalJoin(tbla, tblc);
			}
			catch (const char* error) {
				Assert::AreEqual(error, "tables cannot be naturally joined due to no common column");
			}

			Table* tble = testEngine.naturalJoin(tbla, tblb);

			// verify correct size of naturally joined table
			Assert::IsTrue(tble->getData().size() == 2);

			// verify that new table has correctly merged column titles
			vector<string> columnTitles = tble->getColumnTitles();
			Assert::IsTrue(columnTitles[0] == "name");
			Assert::IsTrue(columnTitles[1] == "school");
			Assert::IsTrue(columnTitles[2] == "age");
			Assert::IsTrue(columnTitles[3] == "city");
			Assert::IsTrue(columnTitles[4] == "state");
			Assert::IsTrue(columnTitles[5] == "studentspeople");

			// verify that new column has correctly merged column types
			vector<string> columnTypes = tble->getColumnTypes();
			Assert::IsTrue(columnTypes[0] == "string");
			Assert::IsTrue(columnTypes[1] == "string");
			Assert::IsTrue(columnTypes[2] == "int");
			Assert::IsTrue(columnTypes[3] == "string");
			Assert::IsTrue(columnTypes[4] == "string");
			Assert::IsTrue(columnTypes[5] == "int");

			// need to check new table and ensure equality where it's needed - hardcoded values are what is expected
			map<string, vector<Attribute*>> tbleData = tble->getData();
			map<string, vector<Attribute*>>::iterator it = tbleData.begin();

			vector<Attribute*> rowa = it->second;
			Assert::IsTrue(rowa[0]->getValue() == "Jacob Zerr");
			Assert::IsTrue(rowa[1]->getValue() == "Kansas University");
			Assert::IsTrue(rowa[2]->getValue() == "75");
			Assert::IsTrue(rowa[3]->getValue() == "San Antonio");
			Assert::IsTrue(rowa[4]->getValue() == "Maryland");
			Assert::IsTrue(rowa[5]->getValue() == "0000000000");
			it++;

			vector<Attribute*> rowb = it->second;
			Assert::IsTrue(rowb[0]->getValue() == "Zach Brown");
			Assert::IsTrue(rowb[1]->getValue() == "Texas A&M");
			Assert::IsTrue(rowb[2]->getValue() == "20");
			Assert::IsTrue(rowb[3]->getValue() == "College Station");
			Assert::IsTrue(rowb[4]->getValue() == "Texas");
			Assert::IsTrue(rowb[5]->getValue() == "0000000001");
		}

		//************************************************************************************************************

		//************************************************************************************************************

		TEST_METHOD(Set_Union){
			// set_union_test
		}

		//************************************************************************************************************

		//************************************************************************************************************

		TEST_METHOD(Set_Difference){
			// set_difference_test
		}
	};
};