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

	};
}