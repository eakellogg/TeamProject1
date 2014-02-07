#include "Engine.h"
#include "Table.h"

int main()
{
	try {
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
	}
	catch (const char* error) {
		cout << error << endl;
		return 1;
	}
	return 0;
}
