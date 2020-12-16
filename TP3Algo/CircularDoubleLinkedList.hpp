// Circular Double Linked List by Romain Bodard.
// List serves as a container for weapons in Game #3.
// Made along with Yannick Côté.

#pragma once
#include <iterator>
#include "EmptyListException.h"

template <class T>
class CircularDoubleLinkedList
{
public:
	CircularDoubleLinkedList();
	~CircularDoubleLinkedList();
	void addEnd(T * value);
	void addStart(T * value);
	T * removeEnd();
	T * removeStart();
	int getCount() const;
	bool isEmpty() const;

private:
	class Cell
	{
	public:
		Cell(Cell * prev, T * value, Cell * next)
		: value(value), prev(prev), next(next) {}
		
		T * value;
		
		Cell * prev;
		Cell * next;		
	};

	int count;

	/// <summary>
	/// This cell is an empty marker for the iterator to stop to.
	/// </summary>
	Cell * dummyCell;


public:
	class iterator 
	: public std::iterator<std::input_iterator_tag, T>
	{
	public:
		iterator(CircularDoubleLinkedList<T> * list, const bool isCirculator = false);
		iterator(const iterator& list_iter, const bool isCirculator = false);
		iterator(Cell* cell, CircularDoubleLinkedList<T>* list, const bool isCirculator = false);

		iterator& operator++();
		iterator operator++(int);

		iterator& operator--();
		iterator operator--(int);

		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;

		T& operator*();

		friend class CircularDoubleLinkedList<T>;

	private:
		const bool isCirculator;
		CircularDoubleLinkedList<T>* list;
		Cell * current;

	};

	iterator begin()
	{
		if (isEmpty())
		{
			return end();
		}

		return iterator(this);
	}

	iterator end()
	{
		return iterator(dummyCell, this);
	}

	void remove(iterator cellToRemove);
};


template <class T>
CircularDoubleLinkedList<T>::CircularDoubleLinkedList(): count(0)
{
	dummyCell = new Cell(nullptr, nullptr, nullptr);
}


template <class T>
CircularDoubleLinkedList<T>::~CircularDoubleLinkedList()
{
	//A pointer is initialised at the beginning of the list.
	Cell* temp = dummyCell->next;

	//Until the list hasn't reached the empty marker... (or is empty)
	while (temp != dummyCell && temp != nullptr)
	{
		Cell *cellToDelete = temp;
		temp = temp->next;
		delete cellToDelete;
	}

	//Then, deletes the cell.
	delete dummyCell;
}

template <class T>
void CircularDoubleLinkedList<T>::addEnd(T* value)
{
	//The cell added before the dummyCell corresponds to the last element of the list.
	dummyCell->prev = new Cell(dummyCell->prev, value, dummyCell);
	
	if (dummyCell->next == nullptr) 
	{
		dummyCell->next = dummyCell->prev;
		dummyCell->prev->prev = dummyCell;
	}

	else 
	{
		dummyCell->prev->prev->next = dummyCell->prev;
	}

	++count;
}

template <class T>
void CircularDoubleLinkedList<T>::addStart(T* value)
{
	//The cell added after the dummyCell corresponds to the first element of the list.
	dummyCell->next = new Cell(dummyCell, value, dummyCell->next);

	if (dummyCell->prev == nullptr) 
	{
		dummyCell->prev = dummyCell->next;
		dummyCell->next->next = dummyCell;
	}
	else 
	{
		dummyCell->next->next->prev = dummyCell->next;
	}

	++count;
}

template <class T>
T * CircularDoubleLinkedList<T>::removeEnd()
{
	//If the end doesn't exist...
	if (dummyCell->prev == nullptr)
	{
		throw EmptyListException();
	}

	T * temp = dummyCell->prev->value;
	if (dummyCell->prev == dummyCell->next)
	{
		delete dummyCell->prev;
		dummyCell->next = dummyCell->prev = nullptr;
	}
	else {
		dummyCell->prev = dummyCell->prev->prev;
		delete dummyCell->prev->next;
		dummyCell->prev->next = dummyCell;
	}

	--count;

	return temp;
}

template <class T>
T * CircularDoubleLinkedList<T>::removeStart()
{
	//If the beginning doesn't exist...
	if(dummyCell->next == nullptr)
	{
		throw EmptyListException();
	}

	T * temp = dummyCell->next->value;
	if(dummyCell->next == dummyCell->prev)
	{
		delete dummyCell->next;
		dummyCell->prev = dummyCell->next = nullptr;
	}
	else
	{
		dummyCell->next = dummyCell->next->next;
		delete dummyCell->next->prev;
		dummyCell->next->prev = dummyCell;
	}

	--count;

	return temp;
}

template <class T>
int CircularDoubleLinkedList<T>::getCount() const
{
	return count;
}

template <class T>
bool CircularDoubleLinkedList<T>::isEmpty() const
{
	return count <= 0;
}

template <class T>
CircularDoubleLinkedList<T>::iterator::iterator(CircularDoubleLinkedList<T>* list, 
	bool isCirculator) : isCirculator(isCirculator), list(list)
{
	if (list == nullptr) {
		current = nullptr;
	}
	else
	{
		current = list->dummyCell->next;
	}
}

template <class T>
CircularDoubleLinkedList<T>::iterator::iterator(const iterator& list_iter, bool isCirculator)
	: current(list_iter.current), isCirculator(isCirculator), list(list_iter.list)
{
}

template <class T>
CircularDoubleLinkedList<T>::iterator::iterator(Cell* cell, CircularDoubleLinkedList<T>* list, bool isCirculator) : 
isCirculator(isCirculator), list(list)
{
	if(cell != nullptr)
	{
		current = cell;
	}
}

template <class T>
typename CircularDoubleLinkedList<T>::iterator& CircularDoubleLinkedList<T>::iterator::operator++()
{
	current = current->next;

	//If this is a circulator and we have reached the dummyCell.
	if(isCirculator && current == list->dummyCell)
	{
		//Skip the dummyCell.a
		current = current->next;
	}

	return *this;
}

template <class T>
typename CircularDoubleLinkedList<T>::iterator CircularDoubleLinkedList<T>::iterator::operator++(int)
{
	iterator tmp(*this);

	operator++();
	return tmp;
}



template <class T>
typename CircularDoubleLinkedList<T>::iterator& CircularDoubleLinkedList<T>::iterator::operator--()
{
	current = current->prev;

	//If this is a circulator and we have reached the dummyCell.
	if(isCirculator && current == list->dummyCell)
	{
		//Skip the dummyCell.
		current = current->prev;
	}
	
	return *this;
}

template <class T>
typename CircularDoubleLinkedList<T>::iterator CircularDoubleLinkedList<T>::iterator::operator--(int)
{
	iterator tmp(*this);

	operator--();
	return tmp;
}

template <class T>
bool CircularDoubleLinkedList<T>::iterator::operator==(const iterator& rhs) const
{
	return current == rhs.current;
}

template <class T>
bool CircularDoubleLinkedList<T>::iterator::operator!=(const iterator& rhs) const
{
	return current != rhs.current;
}

template <class T>
T & CircularDoubleLinkedList<T>::iterator::operator*()
{
	return *current->value;
}

template <class T>
void CircularDoubleLinkedList<T>::remove(iterator i)
{
	Cell* cellToRemove = i.current;
	
	if(cellToRemove == dummyCell)
	{
		//The list shouldn't remove its marker cell, so the method throws
		//an exception
		throw std::exception("The list's marker cell cannot be removed.");
	}

	cellToRemove->prev->next = cellToRemove->next;
	cellToRemove->next->prev = cellToRemove->prev;
	delete cellToRemove;
	--count;

}
