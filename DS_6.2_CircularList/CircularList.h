#ifndef _CIRCULAR_LIST
#define _CIRCULAR_LIST

#include "LinkedList.h"
//#include "LinkedList.cpp"

template<class ItemType>
class CircularList
{
private:
	Node<ItemType>* tailPtr;
	LinkedList<ItemType> listPtr;
	int itemCount;
	int tailPosition;// Locates a specified node in this linked list.
	Node<ItemType>* getNodeAt(int position) const;

public:
	CircularList();
	CircularList(const ItemType& aItem, const int size);
	CircularList(const CircularList<ItemType>& aList);
	~CircularList();

	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const throw(PrecondViolatedExcep);
	int* reversedArray(int array[], int size);

}; // end CircularList
#include "CircularList.cpp"
#endif