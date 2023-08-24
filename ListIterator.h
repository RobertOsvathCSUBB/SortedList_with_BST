#pragma once
#include "SortedIteratedList.h"
#include <stack>

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);

	SortedIteratedList::Node* current;

	std::stack<SortedIteratedList::Node*> stack;

	bool toRight;
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};
