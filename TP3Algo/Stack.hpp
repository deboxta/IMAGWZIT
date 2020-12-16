/// ***** Auteur : Yannick Côté ***** ///
/// ***** Partenaire : Romain Bodard ***** ///
/// ***** Session Automne 2018 ***** ///

#pragma once

namespace TP3Algo
{
	template <class T>
	class Stack
	{
	public:
		Stack();
		~Stack();
		void push(T* value);
		T* pop();
		T& top() const;
		bool isEmpty() const;
		int size() const;

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

		int count = 0;
	};

	template <class T>
	Stack<T>::Stack()
	{
		first = nullptr;
	}

	template<class T>
	Stack<T>::~Stack()
	{
		while (first != nullptr)
		{
			Cell *temp = first;
			first = first->next;
			delete temp;
		}
	}

	template<class T>
	void Stack<T>::push(T* value)
	{
		if (first == nullptr)
		{
			Cell * temp = new Cell(nullptr, value);
			first = temp;
			count++;
		}
		else
		{
			Cell * temp = new Cell(first, value);
			first = temp;
			count++;
		}
	}

	template<class T>
	T * Stack<T>::pop()
	{
		//Ne peut pas pop si la pile est vide
		if (first == nullptr)
		{
			throw std::exception("Empty stack");
		}

		T* valTemp = first->value;
		if (first->next == nullptr)
		{
			delete first;
			first = nullptr;
			--count;
		}
		else {
			Cell* poppedCell = first;
			first = first->next;
			delete poppedCell;
			--count;
		}
		//Renvoie la valeur enlever de la pile
		return valTemp;
	}

	template<class T>
	T & Stack<T>::top()const
	{
		//Ne peut pas envoyer de top si la pile est vide
		if (first == nullptr)
		{
			throw std::exception("No top, empty stack");
		}
		return *first->value;
	}

	template<class T>
	bool Stack<T>::isEmpty()const
	{
		if (first == nullptr)
		{
			return true;
		}
		return false;
	}

	template<class T>
	int Stack<T>::size()const
	{
		return count;
	}
}
