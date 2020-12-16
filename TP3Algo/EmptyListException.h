#pragma once
#include <exception>

class EmptyListException :
	public std::exception
{
public:
	EmptyListException();
	~EmptyListException();
};

