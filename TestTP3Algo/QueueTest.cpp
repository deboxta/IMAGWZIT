/// ***** Auteur : Yannick Côté ***** ///
/// ***** Partenaire : Romain Bodard ***** ///
/// ***** Session Automne 2018 ***** ///

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TP3Algo/Queue.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TP3Algo;

namespace TestTP3Algo
{
	TEST_CLASS(Queue_Test)
	{
	public:

		TEST_METHOD(enqueue_Test_int)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(enqueue_Test_char)
		{
			Queue<char> app;

			char cellValue = 'f';

			app.enqueue(&cellValue);

			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(enqueue_Test_float)
		{
			Queue<float> app;

			float cellValue = 5.5;

			app.enqueue(&cellValue);

			Assert::IsTrue(app.top() == cellValue);
		}

		TEST_METHOD(enqueue_Test_not_empty)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			int cellValue2 = 6;

			app.enqueue(&cellValue2);

			Assert::IsFalse(app.isEmpty());
			Assert::IsTrue(app.top() == 5);
		}

		TEST_METHOD(multiple_operations_Test)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);
			app.dequeue();

			int cellValue2 = 6;

			app.enqueue(&cellValue2);
			app.dequeue();

			Assert::IsTrue(app.isEmpty());
			bool exceptionThrown = false;
			try
			{
				app[0];
			}
			catch (std::exception)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(multiple_operations_Test2)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			int cellValue2 = 6;

			app.enqueue(&cellValue2);
			app.dequeue();

			int cellValue3 = 7;

			app.enqueue(&cellValue3);
			app.dequeue();

			Assert::IsTrue(app.size() == 1);
			Assert::IsTrue(app[0] == 7);
		}

		TEST_METHOD(dequeue_Test_empty)
		{
			Queue<int> app;
			bool exceptionThrown = false;
			try
			{
				app.dequeue();
			}
			catch (std::exception)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(dequeue_Test_not_empty)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			Assert::IsTrue(app.dequeue() == &cellValue);
			Assert::IsTrue(app.isEmpty());
		}

		TEST_METHOD(Operator_access_Test)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			int cellValue2 = 6;

			app.enqueue(&cellValue2);

			int cellValue3 = 7;

			app.enqueue(&cellValue3);

			Assert::IsTrue(app[2] == cellValue3);
		}

		TEST_METHOD(Operator_access_Test2)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			int cellValue2 = 6;

			app.enqueue(&cellValue2);

			int cellValue3 = 7;

			app.enqueue(&cellValue3);

			Assert::IsTrue(app[1] == cellValue2);
		}

		TEST_METHOD(Operator_access_Test_char)
		{
			Queue<char> app;

			char cellValue = 'g';

			app.enqueue(&cellValue);

			char cellValue2 = 'h';

			app.enqueue(&cellValue2);

			char cellValue3 = 'j';

			app.enqueue(&cellValue3);

			Assert::IsTrue(app[1] == cellValue2);
		}

		TEST_METHOD(Operator_access_Test_outside_plus)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			int cellValue2 = 6;

			app.enqueue(&cellValue2);

			int cellValue3 = 7;

			bool exceptionThrown = false;
			try
			{
				app[3];
			}
			catch (std::exception)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(Operator_access_Test_outside_neg)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			int cellValue2 = 6;

			app.enqueue(&cellValue2);

			int cellValue3 = 7;

			bool exceptionThrown = false;
			try
			{
				app[-5];
			}
			catch (std::exception)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(Size_Test)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);
			app.enqueue(&cellValue);
			app.enqueue(&cellValue);

			Assert::IsTrue(app.size() == 3);
		}

		TEST_METHOD(isEmpty_Test_false)
		{
			Queue<int> app;

			int cellValue = 5;

			app.enqueue(&cellValue);

			Assert::IsFalse(app.isEmpty());
		}

		TEST_METHOD(isEmpty_Test_true)
		{
			Queue<int> app;

			Assert::IsTrue(app.isEmpty());
		}

	};
}