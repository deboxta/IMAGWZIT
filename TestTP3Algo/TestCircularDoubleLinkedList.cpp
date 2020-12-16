// Tests for Circular Double Linked List by Romain Bodard.
// List serves as a container for weapons in Game #3.
// Made along with Yannick Côté.

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTP3Algo
{		
	TEST_CLASS(TestCircularDoubleLinkedList)
	{
	public:
		
		TEST_METHOD(TestAddStart01)
		{
			CircularDoubleLinkedList<int> list;
			
			list.addStart(new int(3));
			Assert::AreEqual(3, *list.begin());
		}

		TEST_METHOD(TestAddStart02)
		{
			CircularDoubleLinkedList<float> list;

			list.addStart(new float(188.3546f));

			Assert::AreEqual(188.3546f, *list.begin());
		}

		TEST_METHOD(TestAddStart03)
		{
			CircularDoubleLinkedList<char*> list;

			list.addStart(new char*{ "bazinga!" });

			Assert::AreEqual("bazinga!", *list.begin());
		}

		TEST_METHOD(TestAddEnd01)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(2);

			list.addStart(a);

			int* i = new int(5);

			list.addEnd(i);

			//We bump to the next type so it reaches this list's last type.
			CircularDoubleLinkedList<int>::iterator it = list.begin();
			++it;

			Assert::AreEqual(*i, *it);

			delete a;
			delete i;
		}

		TEST_METHOD(TestAddEnd02)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(18);

			list.addStart(a);
			
			int* i = new int(145);

			list.addEnd(i);

			//We bump to the next type so it reaches this lists' last type.
			CircularDoubleLinkedList<int>::iterator it = list.begin();
			++it;

			Assert::AreEqual(*i, *it);

			delete a;
			delete i;
		}

		TEST_METHOD(TestAddAddRemoveAdd01)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(24325);
			int* b = new int(12);
			int* c = new int(-2335);


			list.addStart(a);
			list.addStart(b);

			//should remove a from the list.
			Assert::AreEqual(list.removeEnd(), a);

			list.addEnd(c);

			CircularDoubleLinkedList<int>::iterator it = list.begin();
			++it;

			Assert::AreEqual(*it, *c);

			delete a, b, c;

		}

		TEST_METHOD(TestRemoveEndEmptyListException)
		{
			CircularDoubleLinkedList<int> list;

			bool exceptionCaught = false;

			try
			{
				list.removeEnd();
			}
			catch (EmptyListException e)
			{
				exceptionCaught = true;
			}

			Assert::IsTrue(exceptionCaught);
		}

		TEST_METHOD(TestRemoveEnd01)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(2);

			list.addStart(a);

			int* i = new int(5);

			list.addEnd(i);

			Assert::AreEqual(i, list.removeEnd());

			delete a;
			delete i;
		}
		

		TEST_METHOD(TestRemoveEnd02)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(18);

			list.addStart(a);

			int* i = new int(49);

			list.addEnd(i);

			Assert::AreEqual(i, list.removeEnd());

			delete a;
			delete i;
		}

		TEST_METHOD(TestRemoveStartEmptyListException)
		{
			CircularDoubleLinkedList<int> list;

			bool exceptionCaught = false;

			try
			{
				list.removeStart();
			}
			catch (EmptyListException e)
			{
				exceptionCaught = true;
			}

			Assert::IsTrue(exceptionCaught);
		}

		TEST_METHOD(TestRemoveStart01)
		{
			CircularDoubleLinkedList<int> list;

			//addStart is equivalent in this context.
			int* a = new int(2);

			list.addEnd(a);

			int* i = new int(5);

			list.addStart(i);

			Assert::AreEqual(i, list.removeStart());

			delete a;
			delete i;
		}

		TEST_METHOD(TestRemoveStart02)
		{
			CircularDoubleLinkedList<int> list;

			//addStart is equivalent in this context.
			int* a = new int(18);

			list.addEnd(a);

			int* i = new int(49);

			list.addStart(i);

			Assert::AreEqual(i, list.removeStart());

			delete a;
			delete i;
		}

		TEST_METHOD(TestIterator01)
		{
			CircularDoubleLinkedList<int*> list;

			int** numList = new int*[4] 
			{
				new int(3),
				new int(7),
				new int(21),
				new int(567)
			};

			for (int i = 0; i < 4; ++i)
			{
				list.addEnd(&numList[i]);
			}

			int i = 0;
			for (int* elem : list)
			{
				Assert::AreEqual(*numList[i],*elem);
				++i;
			}

			delete[] numList;
		}

		TEST_METHOD(TestCount01)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(235);
			int* b = new int(-2343);
			int* c = new int(-12350980968);

			list.addStart(a);
			list.addStart(b);
			list.addStart(c);

			Assert::AreEqual(3, list.getCount());

			delete a, b, c;
		}

		TEST_METHOD(TestCount02)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(235);

			list.addStart(a);

			Assert::AreEqual(1, list.getCount());

			delete a;
		}

		TEST_METHOD(TestIsEmpty)
		{
			CircularDoubleLinkedList<int> list;

			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(TestIsEmptyNegative)
		{
			CircularDoubleLinkedList<int> list;

			int* a = new int(6443);

			list.addStart(a);

			Assert::IsFalse(list.isEmpty());

			delete a;
		}


	};
}