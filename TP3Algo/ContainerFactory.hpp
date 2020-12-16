#pragma once
#include "Stack.hpp"
#include "CircularDoubleLinkedList.hpp"
#include "Queue.hpp"

namespace TP3Algo
{

	template <class T>
	class ContainerFactory
	{
	public:
		static Stack<T>* getStack();
		static Queue<T>* getQueue();
		static CircularDoubleLinkedList<T>* getCircularDoubleLinkedList();
	};

	template <class T>
	Stack<T>* ContainerFactory<T>::getStack()
	{
		return new Stack<T>();
	}

	template <class T>
	Queue<T>* ContainerFactory<T>::getQueue()
	{
		return new Queue<T>();
	}

	template <class T>
	CircularDoubleLinkedList<T>* ContainerFactory<T>::getCircularDoubleLinkedList()
	{
		return new CircularDoubleLinkedList<T>();
	}
}
