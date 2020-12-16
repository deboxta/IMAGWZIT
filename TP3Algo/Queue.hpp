/// ***** Auteur : Yannick Côté ***** ///
/// ***** Partenaire : Romain Bodard ***** ///
/// ***** Session Automne 2018 ***** ///
//test git
#pragma once
#include <deque>

namespace TP3Algo
{
	template <class T>
	class Queue
	{
	public:
		Queue();
		~Queue();
		void enqueue(T* value);
		T* dequeue();
		T& top() const;
		bool isEmpty() const;
		int size() const;

		T& operator[](const int &i);

	private:
		class Cell
		{
		public:
			Cell(Cell * next, T * value)
				: next(next), value(value) {}
			Cell * next;
			T * value;


		};

		Cell * first;
		Cell * last;

		int count = 0;
	};

	template <class T>
	Queue<T>::Queue()
	{
		first = nullptr;
		last = nullptr;
	}

	template<class T>
	Queue<T>::~Queue()
	{
		while (first != nullptr)
		{
			Cell *temp = first;
			first = first->next;
			delete temp;
		}
	}

	template<class T>
	void Queue<T>::enqueue(T* value)
	{
		Cell * temp = new Cell(nullptr, value);
		if (first == nullptr) {
			first = temp;
		}
		else {
			last->next = temp;
		}
		last = temp;
		count++;
	}

	template<class T>
	T * Queue<T>::dequeue()
	{
		//Ne peut pas enlever si la file est vide
		if (first == nullptr)
		{
			throw std::exception("Empty queue");
		}

		Cell* dequeuedCell = first;
		T* valTemp = dequeuedCell->value;

		if (first == last)
		{
			first = nullptr;
			last = nullptr;
			count--;
		}
		else
		{
			first = first->next;
			count--;
		}
		//retourne la valeur enlevée
		delete dequeuedCell;
		return valTemp;
	}

	template<class T>
	T & Queue<T>::top()const
	{
		//Pas de top si la liste est vide
		if (first == nullptr)
		{
			throw std::exception("No top, empty queue");
		}
		return *first->value;
	}

	template<class T>
	bool Queue<T>::isEmpty()const
	{
		if (first == nullptr)
		{
			return true;
		}
		return false;
	}

	template<class T>
	int Queue<T>::size()const
	{
		return count;
	}

	template<class T>
	T & Queue<T>::operator[](const int &i)
	{
		int countIndex = 0;
		Cell * temp = first;
		//Lance une exception lorsque la l'index est sous zéro
		if (isEmpty() == true || i < 0)
		{
			throw std::exception("Index outside the bound of the queue");
		}
		//Lance une exception si l'index est plus grand que la liste
		else if (i >= size())
		{
			throw std::exception("Index outside the bound of the queue");
		}
		else
		{
			//Parcours la liste jusqu'à ce que le compte soit celui voulu
			while (countIndex != i)
			{
				countIndex++;
				temp = temp->next;
			}
		}
		return *temp->value;
	}
}

