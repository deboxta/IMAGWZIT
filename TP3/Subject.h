#pragma once
#include "IObserver.h"
#include <vector>

using std::vector;

class Subject
{
public:
	static void addObserver(IObserver* observer);
	static void removeObserver(IObserver* observer);
	virtual void notifyAllObservers();

protected:
	static vector<IObserver*> observers;
};
