#include "Engine.h"
#include "Table.h"

int main()
{
	try {
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

		vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
		vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
		vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};

		vector<Attribute*> person1 = vector<Attribute*>{namea, citya, statea};
		vector<Attribute*> person2 = vector<Attribute*>{nameb, cityb, stateb};
		vector<Attribute*> person3 = vector<Attribute*>{named, cityc, statec};

		Engine testEngine = Engine();

		testEngine.createTable("students", "name", columnTypesA, columnTitlesA);
		testEngine.createTable("people", "state", columnTypesB, columnTitlesB);

		testEngine.insertInto("students", student1, columnTypesA);
		testEngine.insertInto("students", student2, columnTypesA);
		testEngine.insertInto("students", student3, columnTypesA);

		testEngine.insertInto("people", person1, columnTypesB);
		testEngine.insertInto("people", person2, columnTypesB);
		testEngine.insertInto("people", person3, columnTypesB);

		Table* tbla = testEngine.getTables()[0];
		Table* tblb = testEngine.getTables()[1];

		tbla->printTable();
		tblb->printTable();

		Table* tblc = NULL;
		Table* tbld = NULL;

		tblc = testEngine.crossProduct(tbla, tblb);
		tblc->printTable();

		tbld = testEngine.naturalJoin(tbla, tblb);
		tbld->printTable();
		
	}
	catch (const char* error) {
		cout << error << endl;
		return 1;
	}
	return 0;
}
