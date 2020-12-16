/// ***** Auteur : Yannick Côté ***** ///
/// ***** Partenaire : Romain Bodard ***** ///
/// ***** Session Automne 2018 ***** ///

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TP3Algo/Stack.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TP3Algo;

namespace TestTP3Algo
{		
	TEST_CLASS(Stack_Test)
	{
	public:
		
		TEST_METHOD(Push_Test_int)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);

			Assert::IsFalse(app.isEmpty());
			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(Push_Test_char)
		{
			Stack<char> app;

			char cellValue = 'd';

			app.push(&cellValue);

			Assert::IsFalse(app.isEmpty());
			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(Push_Test_float)
		{
			Stack<float> app;

			float cellValue = 5.5;

			app.push(&cellValue);

			Assert::IsFalse(app.isEmpty());
			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(Push_Test_not_empty)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);

			cellValue = 6;

			app.push(&cellValue);

			Assert::IsFalse(app.isEmpty());
			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(Pop_Test_empty)
		{
			Stack<int> app;

			bool exceptionThrown = false;
			try
			{
				app.pop();
			}
			catch (std::exception)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);


		}
		TEST_METHOD(Pop_Test_not_empty)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);

			Assert::IsTrue(app.pop() == &cellValue);
			Assert::IsTrue(app.isEmpty());
		}

		TEST_METHOD(multiple_operations_Test)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);
			app.pop();

			int cellValue2 = 6;

			app.push(&cellValue2);
			app.pop();

			Assert::IsTrue(app.isEmpty());
		}

		TEST_METHOD(multiple_operations_Test2)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);

			int cellValue2 = 6;

			app.push(&cellValue2);
			app.pop();

			int cellValue3 = 7;

			app.push(&cellValue3);
			app.pop();

			Assert::IsTrue(app.top() == 5);
		}

		TEST_METHOD(Size_Test)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);
			app.push(&cellValue);
			app.push(&cellValue);

			Assert::IsTrue(app.size() == 3);
		}

		TEST_METHOD(isEmpty_Test_false)
		{
			Stack<int> app;

			int cellValue = 5;

			app.push(&cellValue);

			Assert::IsFalse(app.isEmpty());
		}

		TEST_METHOD(isEmpty_Test_true)
		{
			Stack<int> app;

			Assert::IsTrue(app.isEmpty());
		}
	};
}