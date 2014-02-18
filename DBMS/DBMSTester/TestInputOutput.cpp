#include "stdafx.h"
#include "CppUnitTest.h"
#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBMSTester
{
	TEST_CLASS(TestInputOutput)
	{
	public:
		// create information to put into table to prepare testing
		Attribute* namea = new Attribute(STRING_TYPE, "Zach Brown");
		Attribute* nameb = new Attribute(STRING_TYPE, "Jacob Zerr");
		Attribute* namec = new Attribute(STRING_TYPE, "Victoria Elliott");
		Attribute* named = new Attribute(STRING_TYPE, "Johnny Football");

		Attribute* schoola = new Attribute(STRING_TYPE, "Texas A&M");
		Attribute* schoolb = new Attribute(STRING_TYPE, "Kansas University");
		Attribute* schoolc = new Attribute(STRING_TYPE, "Wake Forest");

		Attribute* agea = new Attribute(INT_TYPE, "20");
		Attribute* ageb = new Attribute(INT_TYPE, "75");
		Attribute* agec = new Attribute(INT_TYPE, "18");

		vector<string> columnTypesA = vector<string>{STRING_TYPE, STRING_TYPE, INT_TYPE};

		vector<string> columnTitlesA = vector<string>{"name", "school", "age"};

		vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
		vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
		vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};
		vector<Attribute*> student4 = vector<Attribute*>{named, schoolc, agec};

		DBMS* dbms = new DBMS();
		Engine testEngine = Engine(dbms);

		TEST_METHOD(TestMethod1)
		{
			/*
			testEngine.createTable("students", vector<string>{"name"}, columnTypesA, columnTitlesA);
			testEngine.createTable("studentsbad", vector<string>{"name"}, columnTypesA, columnTitlesA);

			testEngine.insertInto(testEngine.getTables()[0], student1, columnTypesA);
			testEngine.insertInto(testEngine.getTables()[0], student2, columnTypesA);
			testEngine.insertInto(testEngine.getTables()[0], student3, columnTypesA);

			Table* tbla = testEngine.getTables()[0];

			Assert::AreEqual((int)tbla->getData().size(), 3);
			testEngine.writeFile(tbla);

			try {
				testEngine.openFile("studentsbad"); // try to open studentsbad, should throw error 
			}
			catch (const char* error) {
				Assert::AreEqual(error, "the file does not exist"); // nonexistent file of studentsbad.db
			}

			// won't fail because of previous writeFile command
			vector<string> fileLinesA = testEngine.openFile("students");
			Assert::AreEqual((int)fileLinesA.size(), 4);

			// make sure that closing the file included the latest update of adding student4
			Assert::AreEqual(fileLinesA[0],
				(string)"CREATE TABLE students (name VARCHAR(30), school VARCHAR(30), age INTEGER) PRIMARY KEY (name);");
			Assert::AreEqual(fileLinesA[1],
				(string)"INSERT INTO students VALUES FROM (\"Jacob Zerr\", \"Kansas University\", 75);");
			Assert::AreEqual(fileLinesA[2],
				(string)"INSERT INTO students VALUES FROM (\"Victoria Elliott\", \"Wake Forest\", 18);");
			Assert::AreEqual(fileLinesA[3],
				(string)"INSERT INTO students VALUES FROM (\"Zach Brown\", \"Texas A&M\", 20);");
			
			try {
				testEngine.closeFile(testEngine.getTables()[1]); // try to close studentsbad
			}
			catch (const char* error) {
				Assert::AreEqual(error, "the file does not exist"); // nonexistent file of studentsbad.db
			}

			testEngine.insertInto(testEngine.getTables()[0], student4, columnTypesA);

			testEngine.closeFile(testEngine.getTables()[0]); // close students with newly added student

			Assert::AreEqual((int)testEngine.getTables().size(), 1); // make sure table was removed from database
			
			// won't fail because of previous writeFile command
			vector<string> fileLinesB = testEngine.openFile("students");
			Assert::AreEqual((int)fileLinesB.size(), 5);
			
			// make sure that closing the file included the latest update of adding student4
			Assert::AreEqual(fileLinesB[0], 
				(string)"CREATE TABLE students (name VARCHAR(30), school VARCHAR(30), age INTEGER) PRIMARY KEY (name);");
			Assert::AreEqual(fileLinesB[1], 
				(string)"INSERT INTO students VALUES FROM (\"Jacob Zerr\", \"Kansas University\", 75);");
			Assert::AreEqual(fileLinesB[2], 
				(string)"INSERT INTO students VALUES FROM (\"Johnny Football\", \"Wake Forest\", 18);");
			Assert::AreEqual(fileLinesB[3], 
				(string)"INSERT INTO students VALUES FROM (\"Victoria Elliott\", \"Wake Forest\", 18);");
			Assert::AreEqual(fileLinesB[4], 
				(string)"INSERT INTO students VALUES FROM (\"Zach Brown\", \"Texas A&M\", 20);");
				*/
		}
	};
}
