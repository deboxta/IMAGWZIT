#include <iostream>
#include <iterator>
#include "CircularDoubleLinkedList.hpp"
#include "EmptyListException.h"

int main(int argc, char *argv[])
{
	int numbers[] = { 3, 6, 2, 5 };
	auto * list1 = new CircularDoubleLinkedList<int>();
	for (auto & i: numbers)
	{
		list1->addEnd(&i);
	}

	for (auto x : *list1)
	{
		std::cout << "element x: " << x << std::endl;
	}


	std::cout << "removeEnd: " << *list1->removeEnd() << std::endl;
	std::cout << "removeStart: " << *list1->removeStart() << std::endl;

	for (auto x : *list1)
	{
		std::cout << "element x: " << x << std::endl;
	}

	try
	{
		std::cout << "removeEnd: " << *list1->removeEnd() << std::endl;
	}
	catch (EmptyListException e)
	{
		std::cout << "Liste vide!\n";
	}

	system("pause");
	return 0;
}
