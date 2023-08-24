#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedIteratedList.h"
#include "ListIterator.h"
#include <cassert>

bool rel(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

bool even(TComp e)
{
    return e % 2 == 0;
}

bool all(TComp e)
{
	return false;
}

void testFilter()
{
    std::cout << "Test filter" << std::endl;
    SortedIteratedList li{rel};
	for (int i = 1; i <= 100; i++)
		li.add(i);
	li.filter(even);
	for (int i = 1; i <= 100; i++)
	{
		if (even(i))
		{
			assert(li.search(i).getCurrent() == i);
		}
		else
		{
			assert(!li.search(i).valid());
		}
	}
	li.filter(all);
	assert(!li.first().valid());
	assert(li.size() == 0);
}

int main(){
	testFilter();
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}