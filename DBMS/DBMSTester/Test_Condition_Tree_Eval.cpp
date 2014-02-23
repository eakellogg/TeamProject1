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

namespace DBMSTester
{

	TEST_CLASS(ConditionTreeEval){
	public:
		TEST_METHOD(Eval_Condition_Tree_Simple)
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


			Table table("DUMMY", vector<string>{"AGE"}, vector<string>{ INT_LITERAL }, vector<string>{"AGE"});

			string boolean = table.EvalConditionTree(t);

			Assert::AreEqual(FALSE.c_str(), boolean.c_str());
		}
		TEST_METHOD(Eval_Condition_Tree_Recurive)
		{
			TokenStream ts;

			ts.pushToken(Token("JUNK", "THEEND"));//End


			//------------------------------------------------------------------------------
			/*
			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			*/



			//ts.pushToken(Token(OPERATOR, AND)); //This ands right side will be a disjunction

			ts.pushToken(Token(SYMBOL, CLOSE_PAREN));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(OPERATOR, OR));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));

			ts.pushToken(Token(SYMBOL, OPEN_PAREN));

			/*
			ts.pushToken(Token(OPERATOR, AND));

			ts.pushToken(Token(STRING_LITERAL, "Bye"));
			ts.pushToken(Token(OPERATOR, EQUALS));
			ts.pushToken(Token(STRING_LITERAL, "Hello"));
			*/




			ConditionTree* t = parseConditionTree(ts);

			ConditionTree::Node* root = t->getRoot();
			Assert::AreEqual(OPERATOR.c_str(), root->getType().c_str());




			Table table("DUMMY", vector<string>{"AGE"}, vector<string>{ INT_LITERAL }, vector<string>{"AGE"});

			string boolean = table.EvalConditionTree(t);

			Assert::AreEqual(FALSE.c_str(), boolean.c_str());
		}
	};
};