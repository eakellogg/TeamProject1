#include "stdafx.h"
#include "CppUnitTest.h"
#include "EvaluationTree.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBMSTester
{		
	TEST_CLASS(Parser)
	{
	public:
		
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

	};
}