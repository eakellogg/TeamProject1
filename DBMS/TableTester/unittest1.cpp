#include "stdafx.h"
#include "CppUnitTest.h"
#include "Engine.h"
#include "Table.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TableTester
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int a = 2;
			int b = 3;
			Assert::IsTrue(a > 5);
		}

	};
}