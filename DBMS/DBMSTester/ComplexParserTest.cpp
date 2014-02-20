#include "stdafx.h"
#include "CppUnitTest.h"
#include "EvaluationTree.h"
#include "Parser.h"
#include "TokenStream.h"
#include <tuple>
#include "Table.h"
#include "Constants.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/*
In this testing file, I have my parser parse some of the inputs found in the example input file. 
As well as some things that are designed to fail. 
*/
namespace DBMSTester
{

	TEST_CLASS(ComplexParserTest)
	{

		TEST_METHOD(TEST_PARSE_FIRST_EXAMPLE_LINE1)
		{
			TokenStream ts;

			//CREATE TABLE animals ( name VARCHAR(20) , kind VARCHAR(8) , years INTEGER) PRIMARY KEY (name , kind);
			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "kind"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "name"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, PRIMARY_KEY)); //Above (name,kind )

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(TYPE, INT_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "years"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(TYPE, STRING_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "kind"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(TYPE, STRING_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "name"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN)); //Above ( name varchar(20) , .... )

			ts.pushToken(Token(IDENTIFIER, "animals"));

			ts.pushToken(Token(SYMBOL, CREATE_TABLE)); //Above Create Table animals //

			EvaluationTree* tree = parseQuery(ts);

			Assert::AreNotEqual(NULL, (int)tree);
			Assert::AreNotEqual(NULL, (int)tree->getRoot() );

			//Check if the type and value of the root is correct
			Assert::AreNotEqual(PARSE_FAILURE.c_str(), tree->getRoot()->getType().c_str()); 
			Assert::AreEqual(COMMAND_OPERATOR.c_str(), tree->getRoot()->getType().c_str());
			string* command = static_cast<string*>(tree->getRoot()->getValue());
			Assert::AreEqual(CREATE_TABLE.c_str(), (*command).c_str());

			//Get the arguments of the first command
			vector< EvalNodePointer > children = (*tree->getRoot()->getChildren());

			//Check that ther are three agruements
			Assert::AreEqual(size_t(3), children.size());

			Assert::AreEqual (RELATION_NAME.c_str(), children[0]->getType().c_str());
			string* relationName = static_cast<string*>(children[0]->getValue());
			Assert::AreEqual("animals", (*relationName).c_str());

			Assert::AreEqual(ATTRIBUTE_TYPE_PAIR_LIST.c_str(), children[1]->getType().c_str());
			vector< tuple<string , string> >* typenamelist = static_cast< vector< tuple<string , string> >* >(children[1]->getValue());
			
			Assert::AreEqual(size_t(3), typenamelist->size());
			Assert::AreEqual("kind", get<1>((*typenamelist)[1]).c_str()) ;

			Assert::AreEqual(ATTRIBUTE_LIST.c_str(), children[2]->getType().c_str());
			vector< string >*  attributeList = static_cast<  vector< string>* >(children[2]->getValue());
			Assert::AreEqual("kind", (*attributeList)[1].c_str());

		}
		TEST_METHOD(TEST_PARSE_FIRST_EXAMPLE_LINE2)
		{
			//INSERT INTO tools VALUES FROM ("hammer" , 3 , 10 );

			TokenStream ts;
		
			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(INT_LITERAL, "4"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(STRING_LITERAL, "cat"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(STRING_LITERAL, "Joe"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, VALUES_FROM)); //Above Values From ("hammer" , 3 , 10 );


			ts.pushToken(Token(IDENTIFIER, "animals"));

			ts.pushToken(Token(SYMBOL, INSERT)); //Above INSERT INTO animals //

			EvaluationTree* tree = parseQuery(ts);

			Assert::AreNotEqual(NULL, (int)tree);
			Assert::AreNotEqual(NULL, (int)tree->getRoot());

			//Check if the type and value of the root is correct
			Assert::AreNotEqual(PARSE_FAILURE.c_str(), tree->getRoot()->getType().c_str());
			Assert::AreEqual(COMMAND_OPERATOR.c_str(), tree->getRoot()->getType().c_str());
			string* command = static_cast<string*>(tree->getRoot()->getValue());
			Assert::AreEqual(INSERT.c_str(), (*command).c_str());

			//Get the arguments of the first command
			vector< EvalNodePointer > children = (*tree->getRoot()->getChildren());

			//Check that ther are three agruements
			Assert::AreEqual(size_t(2), children.size());

			Assert::AreEqual(RELATION_NAME.c_str(), children[0]->getType().c_str());
			string* relationName = static_cast<string*>(children[0]->getValue());
			Assert::AreEqual("animals", (*relationName).c_str());

			Assert::AreEqual(LITERAL_LIST.c_str(), children[1]->getType().c_str());
			LiteralList* typenamelist = static_cast< LiteralList* >(children[1]->getValue());

			Assert::AreEqual( size_t(3), typenamelist->size());
			Assert::AreEqual("cat", get<1>((*typenamelist)[1]).c_str());


		}

		TEST_METHOD(TEST_PARSE_FIRST_EXAMPLE_LINE7){

			//SHOW animals
			TokenStream ts;
			ts.pushToken(Token(IDENTIFIER, "animals"));
			ts.pushToken(Token(SYMBOL, SHOW));

			EvaluationTree* tree = parseQuery(ts);

			Assert::AreNotEqual(NULL, (int)tree);
			Assert::AreNotEqual(NULL, (int)tree->getRoot());

			//Check if the type and value of the root is correct
			Assert::AreNotEqual(PARSE_FAILURE.c_str(), tree->getRoot()->getType().c_str());
			Assert::AreEqual(COMMAND_OPERATOR.c_str(), tree->getRoot()->getType().c_str());
			string* command = static_cast<string*>(tree->getRoot()->getValue());
			Assert::AreEqual(SHOW.c_str(), (*command).c_str());

			//Get the arguments of the first command
			vector< EvalNodePointer > children = (*tree->getRoot()->getChildren());

			//Check that ther are three agruements
			Assert::AreEqual(size_t(1), children.size());

			Assert::AreEqual(RELATION_NAME.c_str(), children[0]->getType().c_str());
			string* relationName = static_cast<string*>(children[0]->getValue());
			Assert::AreEqual("animals", (*relationName).c_str());

		}
		TEST_METHOD(TEST_PARSE_FIRST_EXAMPLE_LINE8_10_11){

			TokenStream ts;


			ts.pushToken(Token(IDENTIFIER, "animals"));
			ts.pushToken(Token(SYMBOL, EXIT));



			ts.pushToken(Token(IDENTIFIER, "animals"));
			ts.pushToken(Token(SYMBOL, OPEN));


			ts.pushToken(Token(IDENTIFIER, "animals"));
			ts.pushToken(Token(SYMBOL, WRITE));



			EvaluationTree* tree = parseQuery(ts);

			Assert::AreNotEqual(NULL, (int)tree);
			Assert::AreNotEqual(NULL, (int)tree->getRoot());

			//Check if the type and value of the root is correct
			Assert::AreNotEqual(PARSE_FAILURE.c_str(), tree->getRoot()->getType().c_str());
			Assert::AreEqual(COMMAND_OPERATOR.c_str(), tree->getRoot()->getType().c_str());
			string* command = static_cast<string*>(tree->getRoot()->getValue());
			Assert::AreEqual(WRITE.c_str(), (*command).c_str());

			//Get the arguments of the first command
			vector< EvalNodePointer > children = (*tree->getRoot()->getChildren());

			//Check that ther are three agruements
			Assert::AreEqual(size_t(1), children.size());

			Assert::AreEqual(RELATION_NAME.c_str(), children[0]->getType().c_str());
			string* relationName = static_cast<string*>(children[0]->getValue());
			Assert::AreEqual("animals", (*relationName).c_str());

			tree = parseQuery(ts);


			Assert::AreNotEqual(NULL, (int)tree);
			Assert::AreNotEqual(NULL, (int)tree->getRoot());

			//Check if the type and value of the root is correct
			Assert::AreNotEqual(PARSE_FAILURE.c_str(), tree->getRoot()->getType().c_str());
			Assert::AreEqual(COMMAND_OPERATOR.c_str(), tree->getRoot()->getType().c_str());
			command = static_cast<string*>(tree->getRoot()->getValue());
			Assert::AreEqual(OPEN.c_str(), (*command).c_str());

			//Get the arguments of the first command
			children = (*tree->getRoot()->getChildren());

			//Check that ther are three agruements
			Assert::AreEqual(size_t(1), children.size());

			Assert::AreEqual(RELATION_NAME.c_str(), children[0]->getType().c_str());
			 relationName = static_cast<string*>(children[0]->getValue());
			Assert::AreEqual("animals", (*relationName).c_str());


			tree = parseQuery(ts);


			Assert::AreNotEqual(NULL, (int)tree);
			Assert::AreNotEqual(NULL, (int)tree->getRoot());

			//Check if the type and value of the root is correct
			Assert::AreNotEqual(PARSE_FAILURE.c_str(), tree->getRoot()->getType().c_str());
			Assert::AreEqual(COMMAND_OPERATOR.c_str(), tree->getRoot()->getType().c_str());
			command = static_cast<string*>(tree->getRoot()->getValue());
			Assert::AreEqual(EXIT.c_str(), (*command).c_str());

			//Get the arguments of the first command
			children = (*tree->getRoot()->getChildren());

			//Check that ther are three agruements
			Assert::AreEqual(size_t(0), children.size());

		}

		TEST_METHOD(TEST_PARSE_LAST_EXAMPLE_ADVANCED_QUERY)
		{

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
			ts.pushToken(Token(SYMBOL, SELECT));     
			ts.pushToken(Token(SYMBOL, OPEN_PAREN));
			//Above -  (select (y == y2 )


			//----------------------------------------------------------------------
			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "x"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, PROJECT));     //Above - project (x) 
			//-------------------------------------------------------------------

			ts.pushToken(Token(SYMBOL, ARROW));

			ts.pushToken(Token(IDENTIFIER, "advanced_query"));

			EvaluationTree* tree = parseQuery(ts);

			EvalNodePointer root = tree->getRoot();

			Assert::AreEqual(QUERY.c_str(), root->getType().c_str());

			vector< EvalNodePointer > firstArgs = (*root->getChildren());

			Assert::AreEqual((size_t)2, firstArgs.size());


			Assert::AreEqual(RELATION_NAME.c_str(), firstArgs[0]->getType().c_str());

			string relationName = (*(static_cast<string*>(firstArgs[0]->getValue())));
			Assert::AreEqual("advanced_query", relationName.c_str());

			EvalNodePointer rightFirstArg = firstArgs[1];

			string project = *static_cast<string*>(rightFirstArg->getValue());

			Assert::AreEqual(EXPR.c_str(), rightFirstArg->getType().c_str());
			Assert::AreEqual( PROJECTION_EXPR.c_str(), project.c_str());

			vector< EvalNodePointer > secondArgs = *rightFirstArg->getChildren();

			Assert::AreEqual((size_t) 2, secondArgs.size() );

			AttributeList  list = (*(static_cast<AttributeList*>(secondArgs[0]->getValue())));
			Assert::AreEqual("x", list[0].c_str());

			Assert::AreEqual(EXPR.c_str(), secondArgs[1]->getType().c_str());

			EvalNodePointer rightSecondArg = secondArgs[1];

			vector< EvalNodePointer > thirdArgs = *rightSecondArg->getChildren();
			Assert::AreEqual(CONDITION_TREE.c_str(), thirdArgs[0]->getType().c_str());
			Assert::AreEqual(EXPR.c_str(), thirdArgs[1]->getType().c_str());

		}




	};

};