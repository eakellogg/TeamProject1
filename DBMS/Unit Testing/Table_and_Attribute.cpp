#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TableTester
{
	TEST_CLASS(Table_and_Attribute_Testing)
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
	};
};
		
