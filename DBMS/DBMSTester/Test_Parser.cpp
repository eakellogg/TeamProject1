#include "stdafx.h"
#include "CppUnitTest.h"
#include "EvaluationTree.h"
#include "Parser.h"
#include "TokenStream.h"
#include <tuple>
#include "Table.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBMSTester
{		
	TEST_CLASS(Parser)
	{
	public:
		TEST_METHOD(PARSE_CONDITION_TREE)
		{

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ConditionTree* t = parseConditionTree(ts);
		}
		TEST_METHOD(PARSE_COMPARISON)
		{
			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));


			ConditionTree::Node* result = parseComparison(ts);

			Assert::AreEqual(OPERATOR.c_str(), result->getType().c_str());
			Assert::AreEqual(EQUALS.c_str(), result->getValue().c_str());
			vector< ConditionTree::Node*> children = result->getChildern();

			Assert::AreEqual(1, ts.getCount());

			TokenStream ts2;
			ts2.pushToken(Token("JUNK", "THEEND"));

			ConditionTree::Node* result2 = parseComparison(ts2);
			Assert::AreEqual(PARSE_FAILURE.c_str(), result2->getType().c_str());


		}
		TEST_METHOD(PARSE_DIJUNCTION)
		{

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));


			ConditionTree::Node* result = parseDisjunction(ts);

			vector< ConditionTree::Node* > children = result->getChildern();


			Assert::AreEqual((size_t)2, children.size());

			Assert::AreEqual(OPERATOR.c_str(), children[0]->getType().c_str());
			Assert::AreEqual(AND.c_str(), children[0]->getValue().c_str());

			Assert::AreEqual(OPERATOR.c_str(), children[1]->getType().c_str());
			Assert::AreEqual(AND.c_str(), children[1]->getValue().c_str());


			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_CONJUNCTION)
		{
			
			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));


			ConditionTree::Node* result = parseConjunction(ts);

			vector< ConditionTree::Node* > children = result->getChildern();


			Assert::AreEqual((size_t)2, children.size());
			
			Assert::AreEqual(OPERATOR.c_str(), children[0]->getType().c_str());
			Assert::AreEqual(EQUALS.c_str(), children[0]->getValue().c_str());

			Assert::AreEqual(OPERATOR.c_str(), children[1]->getType().c_str());
			Assert::AreEqual(EQUALS.c_str(), children[1]->getValue().c_str());
		
	
			Assert::AreEqual(1, ts.getCount());

		}

		TEST_METHOD(PARSE_OPERAND)
		{
			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(IDENTIFIER, "name"));

			ConditionTree::Node* result1 = parseOperand(ts);
			ConditionTree::Node* result2 = parseOperand(ts);



			Assert::AreEqual(VARIABLE.c_str(), result1->getType().c_str());
			Assert::AreEqual("name", result1->getValue().c_str());

			Assert::AreEqual(STRING_LITERAL.c_str(), result2->getType().c_str());
			Assert::AreEqual("Hello", result2->getValue().c_str() );

			Assert::AreEqual( 1, ts.getCount());

			ConditionTree::Node* result3 = parseOperand(ts);
			Assert::AreEqual(PARSE_FAILURE.c_str(), result3->getType().c_str());

		}
		TEST_METHOD(Parser_Create_EVAL_TREE_Test)
		{
			string* value = new string("<-");
			string* value2 = new string("table1");
			EvaluationTree t(new EvaluationTree::Node(NULL, "OPERATOR", value));

			t.getRoot()->addChild("relation_name", value2);

			EvaluationTree::Node* n = (*t.getRoot()->getChildren())[0];

			string result = (*static_cast<string*>(n->getValue()));


			//is the value of the  child what is expected?
			Assert::AreEqual(result.c_str(), "table1");

		}
		TEST_METHOD(PARSE_RELATIONNAME){

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken( Token(IDENTIFIER.c_str(), "table1"));

			EvalNodePointer result = parseRelationName(ts);

			Assert::AreEqual(RELATION_NAME.c_str(), result->getType().c_str() );

			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual("table1", (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}


		TEST_METHOD(PARSE_TYPE){

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken( Token(TYPE, "VARCHAR") ); //Should this be changed?
			ts.pushToken( Token(TYPE, "INT"));

			EvalNodePointer result1 = parseType(ts);
			EvalNodePointer result2 = parseType(ts);


			Assert::AreEqual(TYPE.c_str(), result1->getType().c_str());
			Assert::AreEqual(TYPE.c_str(), result2->getType().c_str());


			string* value1 = static_cast<string*>(result1->getValue());
			string* value2 = static_cast<string*>(result2->getValue());
			
			Assert::AreEqual(  TYPE.c_str() , result1->getType().c_str() );
			Assert::AreEqual(  TYPE.c_str(), result2->getType().c_str());

			Assert::AreEqual( "INT", (*value1).c_str() );
			Assert::AreEqual( "VARCHAR" , (*value2).c_str());

			Assert::AreEqual(1, ts.getCount());


		}
		TEST_METHOD(PARSE_ATTRIBUTE_VALUE_PAIR)
		{
			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(SYMBOL , ASSIGNMENT));
			ts.pushToken(Token(IDENTIFIER, "word"));

			ts.pushToken(Token(INT_LITERAL, "10"));
			ts.pushToken(Token(SYMBOL, ASSIGNMENT));
			ts.pushToken(Token(IDENTIFIER, "age"));

			EvalNodePointer result = parseAttributeValuePairNode(ts);

			Assert::AreEqual( ATTRIBUTE_VALUE_PAIR_LIST.c_str(), result->getType().c_str());

			vector < tuple< string, string> >* value;
			value = static_cast < vector< tuple<string, string> >* > (result->getValue());

			Assert::AreEqual((size_t)2, value->size());

			vector <tuple <string, string> > vec = *value;

			Assert::AreEqual( "age" , (get<0>( vec[0])).c_str());
			Assert::AreEqual( "10"  , (get<1>(vec[0])).c_str());

			Assert::AreEqual( "word" , (get<0>(vec[1])).c_str() );
			Assert::AreEqual("Hello", (get<1>(vec[1])).c_str());


			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_LITERAL_LIST){

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(INT_LITERAL, "10"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(STRING_LITERAL, "Hello, World"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(INT_LITERAL, "20"));


			EvalNodePointer result = parseLiteralList(ts);
			
			Assert::AreEqual( LITERAL_LIST.c_str(), result->getType().c_str());

			vector < tuple< string, string> >* value;
			value = static_cast < vector< tuple<string, string> >* > ( result->getValue() );

			Assert::AreEqual( (size_t)3, value->size());
			
			vector <tuple <string, string> > vec = *value;

			Assert::AreEqual((get<0>(vec[1])).c_str(), STRING_LITERAL.c_str());
			Assert::AreEqual((get<1>(vec[1])).c_str(), "Hello, World");

			Assert::AreEqual((get<0>(vec[0])).c_str(), INT_LITERAL.c_str());
			Assert::AreEqual("20", (get<1>(vec[0])).c_str() );

			Assert::AreEqual((get<0>((*value)[2])).c_str(), INT_LITERAL.c_str());
			Assert::AreEqual("10", (get<1>((*value)[2])).c_str());

			Assert::AreEqual(1, ts.getCount());
		

		}

		TEST_METHOD(PARSE_TYPED_ATTRIBUTELIST){
			
			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(TYPE, STRING_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "Name"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(TYPE, INT_LITERAL));
			ts.pushToken(Token(IDENTIFIER , "Age"));

			EvalNodePointer result = parseTypedAttributeList(ts);

			vector< tuple<string, string> >* list = static_cast<vector< tuple<string, string> >*> (result->getValue());

			Assert::AreEqual(size_t(2), list->size());

			tuple<string, string> pair1 = (*list)[0];

			Assert::AreEqual(INT_LITERAL.c_str(), get<0>(pair1).c_str());

			Assert::AreEqual( "Age", get<1>(pair1).c_str());


			tuple<string, string> pair2 = (*list)[1];


			Assert::AreEqual(STRING_LITERAL.c_str(), get<0>(pair2).c_str());

			Assert::AreEqual("Name", get<1>(pair2).c_str());

			delete result;
			result = parseTypedAttributeList(ts);

			Assert::AreEqual(PARSE_FAILURE.c_str(), result->getType().c_str());

			Assert::AreEqual(1, ts.getCount());

		}

		TEST_METHOD(PARSE_DELETE)
		{

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(SYMBOL, WHERE));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, DELETE));

			EvalNodePointer result = parseDelete(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
		
			vector< EvalNodePointer >* children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(CONDITION_TREE.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(1, ts.getCount());
		}

		TEST_METHOD(PARSE_INSERT)
		{

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));

			ts.pushToken(Token(INT_LITERAL, "10"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(STRING_LITERAL, "Hello, World"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(INT_LITERAL, "20"));

			ts.pushToken(Token(SYMBOL, VALUES_FROM));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, INSERT));

			EvalNodePointer result = parseInsert(ts);
		


			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			vector< EvalNodePointer >* children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(LITERAL_LIST.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(1, ts.getCount() );


			/*
			TODO write test for second possiblity after testing parseEXPR
			*/

		}

		TEST_METHOD(PARSE_UPDATE)
		{

			TokenStream ts;
			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			//Condtion

			ts.pushToken(Token(SYMBOL, WHERE));

			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(SYMBOL, ASSIGNMENT));
			ts.pushToken(Token(IDENTIFIER, "word"));

			ts.pushToken(Token(INT_LITERAL, "10"));
			ts.pushToken(Token(SYMBOL, ASSIGNMENT));
			ts.pushToken(Token(IDENTIFIER, "age"));

			//Attribute value pairs list

			ts.pushToken(Token(SYMBOL, SET));

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			//RelationName

			ts.pushToken(Token(SYMBOL, UPDATE));

			EvalNodePointer result = parseUpdate(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			vector< EvalNodePointer >* children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(ATTRIBUTE_VALUE_PAIR_LIST.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(CONDITION_TREE.c_str(), (*children)[2]->getType().c_str());

			Assert::AreEqual(1, ts.getCount());



		}
		TEST_METHOD(PARSE_CREATE){

			TokenStream ts;
			ts.pushToken(Token("GARBAGE", "Nothing"));
			ts.pushToken( Token(SYMBOL, CLOSE_PAREN) );

			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));
			// Attribute name list

			ts.pushToken(Token(SYMBOL, PRIMARY_KEY));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(TYPE, STRING_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "Name"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(TYPE, INT_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "Age"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));
			// type-attribute-list

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CREATE_TABLE));

			EvalNodePointer result = parseCreate(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			vector< EvalNodePointer >* children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(ATTRIBUTE_TYPE_PAIR_LIST.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(ATTRIBUTE_LIST.c_str(), (*children)[2]->getType().c_str());


			Assert::AreEqual(1, ts.getCount());

		}

		TEST_METHOD(PARSE_ATTRIBUTE_LIST)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			EvalNodePointer result = parseAttributeList(ts);


			Assert::AreEqual(ATTRIBUTE_LIST.c_str(), result->getType().c_str());

			vector< string >* value = static_cast< vector<string>* > ( result->getValue() );

			Assert::AreEqual(size_t(3), value->size());

			Assert::AreEqual("SCHOOL", (*value)[0].c_str());
			Assert::AreEqual("NAME", (*value)[1].c_str() );
			Assert::AreEqual("AGE", (*value)[2].c_str() );
			
			Assert::AreEqual(1, ts.getCount());

		}

		TEST_METHOD(PARSE_EXIT)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(SYMBOL, EXIT));

			EvalNodePointer result = parseExit(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXIT.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_WRITE)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, WRITE));

			EvalNodePointer result = parseWrite(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(WRITE.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}

		TEST_METHOD(PARSE_CLOSE)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, CLOSE));

			EvalNodePointer result = parseClose(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(CLOSE.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_OPEN)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, OPEN));

			EvalNodePointer result = parseOpen(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			string* value = static_cast<string*>( result->getValue() );
			Assert::AreEqual(OPEN.c_str(), (*value).c_str());


			Assert::AreEqual(1, ts.getCount());
		}

		TEST_METHOD(PARSE_COMMAND)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, OPEN));

			EvalNodePointer result = parseOpen(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(OPEN.c_str(), (*value).c_str());


			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, CLOSE));

			 result = parseClose(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(CLOSE.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, WRITE));

			 result = parseWrite(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(WRITE.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(SYMBOL, EXIT));

			result = parseExit(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());
			 value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXIT.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));
			// Attribute name list

			ts.pushToken(Token(SYMBOL, PRIMARY_KEY));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(TYPE, STRING_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "Name"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(TYPE, INT_LITERAL));
			ts.pushToken(Token(IDENTIFIER, "Age"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));
			// type-attribute-list

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CREATE_TABLE));

		    result = parseCreate(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			vector< EvalNodePointer >* children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(ATTRIBUTE_TYPE_PAIR_LIST.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(ATTRIBUTE_LIST.c_str(), (*children)[2]->getType().c_str());


			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			//Condtion

			ts.pushToken(Token(SYMBOL, WHERE));

			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			ts.pushToken(Token(SYMBOL, ASSIGNMENT));
			ts.pushToken(Token(IDENTIFIER, "word"));

			ts.pushToken(Token(INT_LITERAL, "10"));
			ts.pushToken(Token(SYMBOL, ASSIGNMENT));
			ts.pushToken(Token(IDENTIFIER, "age"));

			//Attribute value pairs list

			ts.pushToken(Token(SYMBOL, SET));

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			//RelationName

			ts.pushToken(Token(SYMBOL, UPDATE));

			result = parseUpdate(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			 children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(ATTRIBUTE_VALUE_PAIR_LIST.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(CONDITION_TREE.c_str(), (*children)[2]->getType().c_str());

			Assert::AreEqual(1, ts.getCount());



			ts.pushToken(Token(INT_LITERAL, "10"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(STRING_LITERAL, "Hello, World"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(INT_LITERAL, "20"));

			ts.pushToken(Token(SYMBOL, VALUES_FROM));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, INSERT));

			result = parseInsert(ts);



			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(LITERAL_LIST.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(SYMBOL, WHERE));
			ts.pushToken(Token(IDENTIFIER, "Table1"));
			ts.pushToken(Token(SYMBOL, DELETE));

			result = parseDelete(ts);

			Assert::AreEqual(COMMAND_OPERATOR.c_str(), result->getType().c_str());

			children = result->getChildren();

			Assert::AreEqual(RELATION_NAME.c_str(), (*children)[0]->getType().c_str());

			Assert::AreEqual(CONDITION_TREE.c_str(), (*children)[1]->getType().c_str());

			Assert::AreEqual(1, ts.getCount());
		}



		TEST_METHOD(PARSE_ATOMIC_EXPR)
		{

			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			EvalNodePointer result = parseAtomicExpr(ts);


			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(RELATION_NAME.c_str(), result->getType().c_str());
			Assert::AreEqual("Table1", (*value).c_str());


		}
		TEST_METHOD(PARSE_EXPR)
		{
			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, JOIN));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			EvalNodePointer  result = parseNaturalJoin(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(JOIN_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, PRODUCT));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			 result = parseProduct(ts);
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(PRODUCT_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, DIFFERENCE));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			result = parseDifference(ts);
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(DIFFERENCE_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, UNION));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			result = parseUnion(ts);
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(UNION_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, RENAME));


			result = parseRenaming(ts);
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(RENAMING_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, PROJECT));


			 result = parseProjection(ts);
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(PROJECTION_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());



			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, SELECT));


			result = parseSelection(ts);
			value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(SELECTION_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

		}
		TEST_METHOD(PARSE_NATURAL_JOIN)
		{

			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, JOIN));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			EvalNodePointer result = parseNaturalJoin(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(JOIN_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_PRODUCT)
		{
			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, PRODUCT));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			EvalNodePointer result = parseProduct(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(PRODUCT_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

		}
		TEST_METHOD(PARSE_DIFFERENCE)
		{
			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, DIFFERENCE));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			EvalNodePointer result = parseDifference(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual( DIFFERENCE_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_UNION)
		{
			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, UNION));

			ts.pushToken(Token(IDENTIFIER, "Table1"));


			EvalNodePointer result = parseUnion(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(UNION_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());
		}
		TEST_METHOD(PARSE_RENAMING){

			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, RENAME));


			EvalNodePointer result = parseRenaming(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(RENAMING_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

			

		}
		TEST_METHOD(PARSE_PROJECTION){

			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(IDENTIFIER, "AGE"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "NAME"));
			ts.pushToken(Token(SYMBOL, COMMA));
			ts.pushToken(Token(IDENTIFIER, "SCHOOL"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, PROJECT));


			EvalNodePointer result = parseProjection(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(PROJECTION_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

		}

		TEST_METHOD(PARSE_SELECTION)
		{
			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));

			ts.pushToken(Token(IDENTIFIER, "Table1"));

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			ts.pushToken(Token(SYMBOL, SELECT));


			EvalNodePointer result = parseSelection(ts);
			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(EXPR.c_str(), result->getType().c_str());
			Assert::AreEqual(SELECTION_EXPR.c_str(), (*value).c_str());

			Assert::AreEqual(1, ts.getCount());

		}
		TEST_METHOD(PARSE_QUERY)
		{

		}
		TEST_METHOD(PARSE_ATTRIBUTE_NAME)
		{
			TokenStream ts;

			ts.pushToken(Token("GARBAGE", "NOTHING"));
			ts.pushToken(Token(IDENTIFIER, "AGE"));

			EvalNodePointer result = parseAttributeName(ts);

			string* value = static_cast<string*>(result->getValue());
			Assert::AreEqual(ATTRIBUTE.c_str(), result->getType().c_str() );
			Assert::AreEqual( "AGE",  (*value).c_str() );

			Assert::AreEqual(1, ts.getCount());
		}
	};
}