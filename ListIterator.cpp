#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list)
{
	this->first();
}

// Total case: O(height of the tree)
void ListIterator::first()
{
	if (this->list.root == nullptr)
	{
		this->current = nullptr;
		return;
	}

	while (!this->stack.empty())
		this->stack.pop();
	
	this->current = this->list.root;
	while (this->current->left != nullptr)
	{
		this->stack.push(this->current);
		this->current = this->current->left;
	}

	if (this->current->right != nullptr)
		this->toRight = true;
	else
		this->toRight = false;
}

// Worst case: the left of the tree is empty and
//				the right side is unbalanced to the 
//				left -> Theta(height of the tree)
// Best case: the iterator needs to move up for the next node -> Theta(1)
// Total case: O(height of the tree)
void ListIterator::next()
{	
	if (!this->valid())
		throw exception();
	
	if (this->toRight)
	{
		this->current = this->current->right;
		if (this->current == nullptr)
			goto MOVE_UP;
		while (this->current->left != nullptr)
		{
			this->stack.push(this->current);
			this->current = this->current->left;
		}
		if (this->current->right != nullptr)
			this->toRight = true;
		else
			this->toRight = false;
	}
	else
	{
		MOVE_UP:
		if (this->stack.size() == 0)
		{
			this->current = nullptr;
			return;
		}
		this->current = this->stack.top();
		this->stack.pop();
		this->toRight = true;
	}
}

bool ListIterator::valid() const
{
	return this->current != nullptr;
}

TComp ListIterator::getCurrent() const
{
	if (!this->valid())
		throw exception();
	return this->current->val;
}


