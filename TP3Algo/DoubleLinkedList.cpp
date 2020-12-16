#include "DoubleLinkedList.h"
#include "EmptyListException.h"


template <class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	first = nullptr;
	last = nullptr;
}


template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	while(first != nullptr)
	{
		Cell *temp = first;
		first = first->next;
		delete temp;
	}
}

template <class T>
void DoubleLinkedList<T>::add_end(T* value)
{
	last = new Cell(last, value, nullptr);
	if (first == nullptr) {
		first = last;
	} else {
		last->prev->next = last;
	}
}

template <class T>
void DoubleLinkedList<T>::add_start(T* value)
{
	first = new Cell(nullptr, value, first);
	if (last == nullptr) {
		last = first;
	}
	else {
		first->next->prev = first;
	}
}

template <class T>
T * DoubleLinkedList<T>::remove_end()
{
	if (last == nullptr)
	{
		throw EmptyListException();
	}

	int temp = last->value;
	if (last == first)
	{
		delete last;
		first = last = nullptr;
	}
	else {
		last = last->prev;
		delete last->next;
		last->next = nullptr;
	}
	return temp;
}

template <class T>
T * DoubleLinkedList<T>::remove_start()
{
	return nullptr;
}

template <class T>
DoubleLinkedList<T>::iterator::iterator(const DoubleLinkedList<T>* list)
{
	if (list == nullptr) {
		current = nullptr;
	} else
	{
		current = list->first;
	}
}

template <class T>
DoubleLinkedList<T>::iterator::iterator(const iterator& list_iter)
	: current(list_iter.current)
{
}

template <class T>
typename DoubleLinkedList<T>::iterator& DoubleLinkedList<T>::iterator::operator++()
{
	current = current->next;
	return *this;
}

template <class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::iterator::operator++(int)
{
	iterator tmp(*this);
	operator++();
	return tmp;
}

template <class T>
bool DoubleLinkedList<T>::iterator::operator==(const iterator& rhs) const
{
	return current == rhs.current;
}

template <class T>
bool DoubleLinkedList<T>::iterator::operator!=(const iterator& rhs) const
{
	return current != rhs.current;
}

template <class T>
T & DoubleLinkedList<T>::iterator::operator*()
{
	return current->value;
}

