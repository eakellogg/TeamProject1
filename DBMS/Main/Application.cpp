#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"
#include "Evaluator.h"

int main()
{
	try {
		/*
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

		Attribute* citya = new Attribute(STRING_TYPE, "College Station");
		Attribute* cityb = new Attribute(STRING_TYPE, "San Antonio");
		Attribute* cityc = new Attribute(STRING_TYPE, "Frederick");

		Attribute* statea = new Attribute(STRING_TYPE, "Texas");
		Attribute* stateb = new Attribute(STRING_TYPE, "Maryland");
		Attribute* statec = new Attribute(STRING_TYPE, "Missouri");

		vector<string> columnTypesA = vector<string>{STRING_TYPE, STRING_TYPE, INT_TYPE};
		vector<string> columnTypesB = vector<string>{STRING_TYPE, STRING_TYPE, STRING_TYPE};
		vector<string> badColumnTypes = vector<string>{INT_TYPE, INT_TYPE, INT_TYPE};

		vector<string> columnTitlesA = vector<string>{"name", "school", "age"};
		vector<string> columnTitlesB = vector<string>{"name", "city", "state"};
		vector<string> renamedTitles = vector<string>{"newname", "school", "age"};

		vector<Attribute*> student1 = vector<Attribute*>{namea, schoola, agea};
		vector<Attribute*> student2 = vector<Attribute*>{nameb, schoolb, ageb};
		vector<Attribute*> student3 = vector<Attribute*>{namec, schoolc, agec};
		vector<Attribute*> student4 = vector<Attribute*>{named, schoolc, agec};

		vector<Attribute*> person1 = vector<Attribute*>{namea, citya, statea};
		vector<Attribute*> person2 = vector<Attribute*>{nameb, cityb, stateb};
		vector<Attribute*> person3 = vector<Attribute*>{named, cityc, statec};

		DBMS* dbms = new DBMS();
		Engine testEngine = Engine(dbms);

		testEngine.createTable("students", vector<string>{"name", "age"}, columnTypesA, columnTitlesA);
		testEngine.createTable("people", vector<string>{"state"}, columnTypesB, columnTitlesB);
		testEngine.createTable("otherstudents", vector<string>{"age"}, columnTypesA, columnTitlesA);
		testEngine.createTable("otherstudentstest", vector<string>{"age"}, columnTypesA, columnTitlesA);

		testEngine.insertInto(testEngine.getTables()[0], student1, columnTypesA);
		testEngine.insertInto(testEngine.getTables()[0], student2, columnTypesA);
		testEngine.insertInto(testEngine.getTables()[0], student3, columnTypesA);
		testEngine.insertInto(testEngine.getTables()[2], student4, columnTypesA);

		testEngine.insertInto(testEngine.getTables()[1], person1, columnTypesB);
		testEngine.insertInto(testEngine.getTables()[1], person2, columnTypesB);
		testEngine.insertInto(testEngine.getTables()[1], person3, columnTypesB);

		Table* tbla = testEngine.getTables()[0];
		Table* tblb = testEngine.getTables()[1];
		
		ConditionTree t(OPERATOR, AND);
		ConditionTree::Node* n = t.getRoot();

		//ConditionTree::Node* firstEQ = n->addChild(OPERATOR, GREATER_EQUAL);
		//firstEQ->addChild(INT_LITERAL, "5");
		//firstEQ->addChild(VARIABLE, "age");

		ConditionTree::Node* secondEQ = n->addChild(OPERATOR, NOT_EQUAL);
		secondEQ->addChild(STRING_LITERAL, "Victoria Elliott");
		secondEQ->addChild(VARIABLE, "name");
		
		// test each relational algebra method
		Table* tblc = NULL;

		cout << "selection:" << endl;
		tblc = testEngine.selection(tbla, t);
		tblc->printTable();
		
		cout << "projection:" << endl;
		vector<string> wantedColumns = {"name", "school"};
		tblc = testEngine.selection(testEngine.projection(tbla, wantedColumns),t);
		tblc->printTable();

		//cout << "rename:" << endl;
		//tblc = testEngine.selection(testEngine.rename(tbla, renamedTitles), t);
		//tblc->printTable();

		cout << "union:" << endl;
		tblc = testEngine.setUnion(tbla, testEngine.getTables()[2]);
		tblc->printTable();

		//cout << "difference:" << endl;
		//tblc = testEngine.setDifference(tbla, testEngine.getTables()[2]);
		//tblc->printTable();

		cout << "cross product:" << endl;
		tblc = testEngine.crossProduct(tbla, tblc);
		tblc->printTable();

		cout << "natural join:" << endl;
		tblc = testEngine.naturalJoin(tbla, tblb);
		tblc->printTable();

		vector<string> fileLines;
		fileLines = testEngine.openFile("students");
		for (int i = 0; i < fileLines.size(); i++) {
			cout << fileLines[i] << endl;
		}
		testEngine.writeFile(tbla);
		testEngine.insertInto(testEngine.findTable("students"), student4, columnTypesA);
		//testEngine.writeFile(tbla);
		testEngine.closeFile(tbla);
		//testEngine.writeFile(tblb);
		//testEngine.closeFile(tblb);
		*/


DBMS* dbms = new DBMS;
Engine* engine = new Engine(dbms);
Evaluator eval = Evaluator(engine);


TokenStream ts;

ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

ts.pushToken(Token(IDENTIFIER, "name"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(IDENTIFIER, "age"));

ts.pushToken(Token(SYMBOL, OPEN_PAREN));
// Attribute name list

ts.pushToken(Token(SYMBOL, PRIMARY_KEY));

ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

ts.pushToken(Token(TYPE, STRING_LITERAL));
ts.pushToken(Token(IDENTIFIER, "school"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(TYPE, STRING_LITERAL));
ts.pushToken(Token(IDENTIFIER, "name"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(TYPE, INT_LITERAL));
ts.pushToken(Token(IDENTIFIER, "age"));

ts.pushToken(Token(SYMBOL, OPEN_PAREN));
// type-attribute-list

ts.pushToken(Token(IDENTIFIER, "Table1"));

ts.pushToken(Token(SYMBOL, CREATE_TABLE));

EvaluationTree* tree = parseQuery(ts);
eval.Evaluate(tree);

ts.pushToken(Token(SYMBOL, CLOSE_PAREN));
ts.pushToken(Token(STRING_LITERAL, "TAMU"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(STRING_LITERAL, "Nathan De Jong"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(INT_LITERAL, "20"));
ts.pushToken(Token(SYMBOL, OPEN_PAREN));

ts.pushToken(Token(SYMBOL, VALUES_FROM));
ts.pushToken(Token(IDENTIFIER, "Table1"));
ts.pushToken(Token(SYMBOL, INSERT));

tree = parseQuery(ts);
eval.Evaluate(tree);

ts.pushToken(Token(SYMBOL, CLOSE_PAREN));
ts.pushToken(Token(STRING_LITERAL, "RICE"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(STRING_LITERAL, "Zach Brown"));
ts.pushToken(Token(SYMBOL, COMMA));
ts.pushToken(Token(INT_LITERAL, "91"));
ts.pushToken(Token(SYMBOL, OPEN_PAREN));

ts.pushToken(Token(SYMBOL, VALUES_FROM));
ts.pushToken(Token(IDENTIFIER, "Table1"));
ts.pushToken(Token(SYMBOL, INSERT));

tree = parseQuery(ts);
eval.Evaluate(tree);

ts.pushToken(Token(IDENTIFIER, "Table1"));

ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

ts.pushToken(Token(STRING_LITERAL, "RICE"));
ts.pushToken(Token(OPERATOR, EQUALS));
ts.pushToken(Token(IDENTIFIER, "school"));

ts.pushToken(Token(SYMBOL, OPEN_PAREN));

ts.pushToken(Token(SYMBOL, SELECT));

ts.pushToken(Token(SYMBOL, ARROW));
ts.pushToken(Token(IDENTIFIER, "Query1"));

tree = parseQuery(ts);
Table* tbl = eval.Evaluate(tree);

tbl->printTable();

ts.pushToken(Token(STRING_LITERAL, "RICE"));
ts.pushToken(Token(OPERATOR, EQUALS));
ts.pushToken(Token(IDENTIFIER, "school"));

ts.pushToken(Token(SYMBOL, WHERE));
ts.pushToken(Token(IDENTIFIER, "Table1"));
ts.pushToken(Token(SYMBOL, DELETE));

tree = parseQuery(ts);
eval.Evaluate(tree);

engine->getTables()[0]->printTable();

	}
	catch (const char* error) {
		cout << error << endl;
		return 1;
	}
	
	return 0;
}
