#include "CircularList.h"
#include <cassert>

template<class ItemType>
CircularList<ItemType>::CircularList() : itemCount(0), tailPosition(0), listPtr(new LinkedList<ItemType>())
{
    tailPtr = nullptr;
}  // end default constructor

template<class ItemType>
CircularList<ItemType>::CircularList(const ItemType& anItem, const int size) : itemCount(size), tailPosition(size), listPtr(new LinkedList<ItemType>())
{
    // Add the first item
    listPtr->insert(1, anItem);
    Node<ItemType>* newNodePtr = listPtr->getNodeAt(1);

    // Add the remaining items
    for (int i = 2; i <= size; i++)
    {
        listPtr->insert(i, anItem);
        newNodePtr = listPtr->getNodeAt(i);
    }

    // Set tail node and head node
    tailPtr = newNodePtr;
    tailPtr->setNext(listPtr->getNodeAt(1));
}  // end constructor

template<class ItemType>
CircularList<ItemType>::CircularList(const CircularList<ItemType>& aList)
{
    itemCount = aList.itemCount;
    tailPosition = aList.tailPosition;

    // Copy the linked list
    listPtr = new LinkedList<ItemType>(*aList.listPtr);

    // Set tail node and head node
    tailPtr = listPtr->getNodeAt(tailPosition);
    tailPtr->setNext(listPtr->getNodeAt(1));
}  // end copy constructor

template<class ItemType>
CircularList<ItemType>::~CircularList()
{
    clear();
    delete listPtr;
    listPtr = nullptr;
}  // end destructor

template<class ItemType>
bool CircularList<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int CircularList<ItemType>::getLength() const
{
    return itemCount;
}  // end getLength

template<class ItemType>
bool CircularList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    bool ableToInsert = listPtr->insert(newPosition, newEntry);

    if (ableToInsert && itemCount == 0)
    {
        listPtr->getNodeAt(1)->setNext(listPtr->getNodeAt(1));
    }
    else if (ableToInsert && itemCount == 1)
    {
        listPtr->getNodeAt(2)->setNext(listPtr->getNodeAt(1));
        listPtr->getNodeAt(1)->setNext(listPtr->getNodeAt(2));
    }
    else if (ableToInsert && itemCount > 1)
    {
        if (newPosition == 1)
        {
            listPtr->getNodeAt(itemCount + 1)->setNext(listPtr->getNodeAt(1));
            listPtr->getNodeAt(1)->setNext(listPtr->getNodeAt(2));
        }
        else if (newPosition == itemCount)
        {
            listPtr->getNodeAt(itemCount)->setNext(listPtr->getNodeAt(itemCount + 1));
        }
        else
        {
            listPtr->getNodeAt(itemCount + 1)->setNext(listPtr->getNodeAt(1));
        }
    }

    itemCount = listPtr->getLength();

    return ableToInsert;
}  // end insert

template<class ItemType>
bool CircularList<ItemType>::remove(int position)
{
    bool ableToRemove = listPtr->remove(position);

    if (ableToRemove && itemCount == 1)
    {
        listPtr->getNodeAt(1)->setNext(nullptr);
    }
    else if (ableToRemove && itemCount == 2)
    {
        listPtr->getNodeAt(1)->setNext(listPtr->getNodeAt(2));
        listPtr->getNodeAt(2)->setNext(listPtr->getNodeAt(1));
    }
    else if (ableToRemove && itemCount > 2)
    {
        if (position == 1)
        {
            listPtr->getNodeAt(itemCount)->setNext(listPtr->getNodeAt(2));
        }
        else if (position == itemCount)
        {
            listPtr->getNodeAt(itemCount - 1)->setNext(listPtr->getNodeAt(1));
        }
    }

    itemCount = listPtr->getLength();

    return ableToRemove;

    /*
   bool ableToRemove = listPtr->remove(position);
   if (ableToRemove && itemCount == 0)
   {
       tailPtr = nullptr;
   }
   else if (ableToRemove && itemCount == 1)
   {
       tailPtr = listPtr->getNodeAt(1);
       tailPtr->setNext(listPtr->getNodeAt(1));
   }
   else if (ableToRemove && itemCount > 1)
   {
       if (position == 1)
       {
           tailPtr->setNext(listPtr->getNodeAt(2));
       }
       else if (position == itemCount)
       {
           tailPtr = listPtr->getNodeAt(itemCount - 1);
           tailPtr->setNext(listPtr->getNodeAt(1));
       }
   }
   itemCount = listPtr->getLength();
   return ableToRemove;*/

}  // end remove    

template<class ItemType>
void CircularList<ItemType>::clear()
{
	listPtr->clear();
    listPtr->getNodeAt(1)->setNext(listPtr->getNodeAt(1));
    itemCount = 0;
}  // end clear

template<class ItemType>
ItemType CircularList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
    return listPtr->getEntry(position);
}  // end getEntry

template<class ItemType>
int* CircularList<ItemType>::reversedArray(int array[], int size)
{
    LinkedList<ItemType> list;
    for (int i = size - 1; i >= 0; i--)
    {
        ItemType item = arr[i];
        list.insert(list.getLength() + 1, item);
    }

    // Make it a circular list with a dummy node that unionizes the tail node with the head node
    Node<ItemType>* tailNode = list.getNodeAt(list.getLength());
    tailNode->setNext(list.headPtr);
    list.itemCount++;
    return list;
}  // end reversedArray

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
    // Debugging check of precondition
    assert((position >= 1) && (position <= itemCount));

    // Count from the beginning of the chain
    Node<ItemType>* curPtr = headPtr;
    for (int skip = 1; skip < position; skip++)
        curPtr = curPtr->getNext();

    return curPtr;
}  // end getNodeAt