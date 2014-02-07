#include "Engine.h"
#include "Table.h"

int main()
{

	try {

		Engine engine = Engine();
		vector<string> rowTypes = vector<string>{"string", "string", "int"};
		vector<string> badRowTypes = vector<string>{"string", "string", "string"};
		vector<string> columnTitles = vector<string>{"name", "school", "age"};

		vector<string> student1 = vector<string>{"Zach Brown", "TAMU", "20"};
		vector<string> student2 = vector<string>{"Jacob Zerr", "KU", "75"};
		vector<string> student3 = vector<string>{"Victoria Elliott", "Wake Forest", "18"};


		engine.createTable("students", rowTypes, columnTitles);
		engine.insertInto("students", student1, rowTypes);
		engine.insertInto("students", student2, rowTypes);
		//engine.insertInto("students", student3, badRowTypes);
		//engine.insertInto("badname", student3, rowTypes);
		//engine.update("students", student3, rowTypes);
		cout << engine.getTables()[0]->getRow(0)[2];

		cout << engine.getTables().size();
		engine.dropTable("students");
		//cout << engine.getTables().size();
	}
	catch (const char* error) {
		cout << error << endl;
	}

	return 0;
}
