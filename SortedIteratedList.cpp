#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>
#include <functional>

SortedIteratedList::SortedIteratedList(Relation r) : rel(r)
{
	this->root = nullptr;
	this->totalSize = 0;
}

// Theta(1)
int SortedIteratedList::size() const
{
	return this->totalSize;
}

// Theta(1)
bool SortedIteratedList::isEmpty() const
{
	return this->totalSize == 0;
}

ListIterator SortedIteratedList::first() const
{
	return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator pos) const
{
	return pos.getCurrent();
}

// Best case: the iterator points to the root, and the left subtree 
//				has only one element -> Theta(1)
// Worst case: the iterator points to the leftmost element (the minimum)
//				which is also the furthest from the root 
//				-> Theta(height of the tree)
// Total case: O(height of the tree)
TComp SortedIteratedList::remove(ListIterator& pos)
{
	if (!pos.valid())
		throw exception();

	Node* parent = nullptr;
	Node* current = this->root;
	while (true)
	{
		if (current == pos.current)
			break;
		else if (this->rel(pos.getCurrent(), current->val))
		{
			parent = current;
			current = current->left;
		}
		else
		{
			parent = current;
			current = current->right;
		}
	}
	
	Node* nodeToRemove = current;
	if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr)
	{
		TComp value = nodeToRemove->val;
		if (parent == nullptr)
			this->root = nullptr;
		else if (parent->left == nodeToRemove)
			parent->left = nullptr;
		else
			parent->right = nullptr;
		this->totalSize--;
		pos.next();
		delete nodeToRemove;
		return value;
	}
	if (nodeToRemove->left == nullptr)
	{
		TComp value = nodeToRemove->val;
		if (parent == nullptr)
			this->root = this->root->right;
		else if (parent->left == nodeToRemove)
			parent->left = nodeToRemove->right;
		else
			parent->right = nodeToRemove->right;
		this->totalSize--;
		pos.next();
		return value;
	}
	if (nodeToRemove->right == nullptr)
	{
		TComp value = nodeToRemove->val;
		if (parent == nullptr)
			this->root = this->root->left;
		else if (parent->left == nodeToRemove)
			parent->left = nodeToRemove->left;
		else
			parent->right = nodeToRemove->left;
		this->totalSize--;
		pos.next();
		return value;
	}
	TComp value = nodeToRemove->val;
	Node* maxParent = nodeToRemove;
	Node* max = nodeToRemove->left;
	while (max->right != nullptr)
	{
		maxParent = max;
		max = max->right;
	}
	nodeToRemove->val = max->val;
	if (max->left == nullptr && max->right == nullptr)
	{
		if (maxParent->left == max)
			maxParent->left = nullptr;
		else
			maxParent->right = nullptr;
		delete max;
	}
	else if (max->left == nullptr)
	{
		if (maxParent->left == max)
			maxParent->left = max->right;
		else
			maxParent->right = max->right;
		delete max;
	}
	else
	{
		if (maxParent->left == max)
			maxParent->left = max->left;
		else
			maxParent->right = max->left;
		delete max;
	}
	this->totalSize--;
	pos.next();
	return value;
}

// Best case: the element is the minimum -> Theta(height of the tree)
// Worst case: the element is the maximum -> Theta(totalSize ^ 2)
//				(if the tree is unbalanced)
// Total case: O(totalSize ^ 2)
ListIterator SortedIteratedList::search(TComp e) const
{
	ListIterator it{ *this };
	while (it.valid() && it.getCurrent() != e)
		it.next();
	return it;
}

// Total case: Theta(height of the tree)
void SortedIteratedList::add(TComp e)
{	
	Node* newNode = new Node(e);
	std::function<Node*(Node*)> add_recursive = [&](Node* root)
	{
		if (root == nullptr)
		{
			root = newNode;
			return root;
		}
		if (this->rel(newNode->val, root->val))
		{
			root->left = add_recursive(root->left);
		}
		else
			root->right = add_recursive(root->right);
		return root;
	};
	this->root = add_recursive(this->root);
	this->totalSize++;
}

// Theta(height of the tree)
SortedIteratedList::~SortedIteratedList()
{
	std::function<void(Node*)> destroy = [&](Node* current)
	{
		if (current != nullptr)
		{
			destroy(current->left);
			destroy(current->right);
			delete current;
		}
	};
	destroy(this->root);
}

// Total case: O(totalSize ^ 2)
void SortedIteratedList::filter(Condition cond)
{
	ListIterator it = this->first();
	while (it.valid())
	{
		TComp e = it.getCurrent();
		if (!cond(e))
			this->remove(it);
		else
			it.next();
	}
}
