#include "Engine.h"
#include "Table.h"
#include "TokenStream.h"
#include "Parser.h"
#include "Constants.h"

int main()
{
	/*
	TokenStream ts;
	ts.pushToken(Token(SYMBOL, CLOSE_PAREN));
	ts.pushToken(Token(INT_LITERAL, "10"));
	ts.pushToken(Token(SYMBOL, COMMA));
	ts.pushToken(Token(STRING_LITERAL, "Hello, World"));
	ts.pushToken(Token(SYMBOL, COMMA));
	ts.pushToken(Token(INT_LITERAL, "20"));
	ts.pushToken(Token(SYMBOL, OPEN_PAREN));
	ts.pushToken(Token(SYMBOL, VALUES_FROM));
	ts.pushToken(Token(IDENTIFIER, "Table1"));
	ts.pushToken(Token(SYMBOL, INSERT));

	EvalNodePointer result = parseInsert(ts);

	cout << result->getType() << endl;
	
	TokenStream ts;

	ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

	ts.pushToken(Token(IDENTIFIER, "dots_to_points"));
	ts.pushToken(Token(SYMBOL, PRODUCT));
	ts.pushToken(Token(IDENTIFIER, "points"));

	ts.pushToken(Token(SYMBOL, OPEN_PAREN)); //Above -  (points * dots_to_points ))

	EvalNodePointer tree = parseAtomicExpr(ts);
	
	cout << tree->getType() << endl;
	
	//advanced_query <- project(x) (select(y == y2) (points * dots_to_points));
	
	
	TokenStream ts;

	ts.pushToken(Token(SYMBOL, CLOSE_PAREN));
	ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

	ts.pushToken(Token(IDENTIFIER, "dots_to_points"));
	ts.pushToken(Token(SYMBOL, PRODUCT));
	ts.pushToken(Token(IDENTIFIER, "points"));

	ts.pushToken(Token(SYMBOL, OPEN_PAREN)); //Above -  (points * dots_to_points ))


	//------------------------------------------------------
	ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

	ts.pushToken(Token(IDENTIFIER, "y2"));
	ts.pushToken(Token(SYMBOL, EQUALS));
	ts.pushToken(Token(IDENTIFIER, "y"));

	ts.pushToken(Token(SYMBOL, OPEN_PAREN));
	ts.pushToken(Token(SYMBOL, SELECT));     //Above -  (select (y == y2 )
	ts.pushToken(Token(SYMBOL, OPEN_PAREN));
	//----------------------------------------------------------------------
	ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

	ts.pushToken(Token(IDENTIFIER, "x"));

	ts.pushToken(Token(SYMBOL, OPEN_PAREN));

	ts.pushToken(Token(SYMBOL, PROJECT));     //Above - project (x) 
	//-------------------------------------------------------------------

	ts.pushToken(Token(SYMBOL, ARROW));
	ts.pushToken(Token(IDENTIFIER, "avanced_query"));

	EvaluationTree* tree = parseQuery(ts);

	EvalNodePointer root = tree->getRoot();

	cout << root->getType() << endl;
	*/
	try {

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

		testEngine.createTable("students", vector<string>{"name"}, columnTypesA, columnTitlesA);
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
		
		ConditionTree t(OR, OPERATOR);
		ConditionTree::Node* n = t.getRoot();

		ConditionTree::Node* firstEQ = n->addChild(EQUALS, OPERATOR);
		firstEQ->addChild("Zach Brown", STRING_LITERAL);
		firstEQ->addChild("name", VARIABLE);

		ConditionTree::Node* secondEQ = n->addChild(EQUALS, OPERATOR);
		secondEQ->addChild("Jacob Zerr", STRING_LITERAL);
		secondEQ->addChild("name", VARIABLE);
		
		// test each relational algebra method
		Table* tblc = NULL;

		//cout << "selection:" << endl;
		//tblc = testEngine.selection(tbla, t);
		//tblc->printTable();

		cout << "projection:" << endl;
		vector<string> wantedColumns = {"name", "age"};
		tblc = testEngine.projection(tbla, wantedColumns);
		tblc->printTable();

		cout << "rename:" << endl;
		tblc = testEngine.rename(tbla, renamedTitles);
		tblc->printTable();

		cout << "union:" << endl;
		tblc = testEngine.setUnion(tbla, testEngine.getTables()[2]);
		tblc->printTable();

		cout << "difference:" << endl;
		tblc = testEngine.setDifference(tbla, testEngine.getTables()[2]);
		tblc->printTable();

		cout << "cross product:" << endl;
		tblc = testEngine.crossProduct(tbla, tblb);
		tblc->printTable();

		cout << "natural join:" << endl;
		tblc = testEngine.naturalJoin(tbla, tblb);
		tblc->printTable();

		vector<string> fileLines;
		fileLines = testEngine.openFile("students");
		for (int i = 0; i < fileLines.size(); i++) {
			cout << fileLines[i] << endl;
		}
		//testEngine.writeFile(tbla);
		testEngine.insertInto(testEngine.findTable("students"), student4, columnTypesA);
		//testEngine.writeFile(tbla);
		testEngine.closeFile(tbla);
		//testEngine.writeFile(tblb);
		//testEngine.closeFile(tblb);
	}
	catch (const char* error) {
		cout << error << endl;
		return 1;
	}
	
	return 0;
}
