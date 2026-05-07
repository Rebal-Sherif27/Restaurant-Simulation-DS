/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"
#include <iostream>

using namespace std;

template <typename T>
class LinkedQueue :public QueueADT<T>
{
protected:  //in case you need to inherit for the project
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count; // FIXED: Changed 'Count' to 'count'

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>& LQ); // FIXED: Added missing copy constructor

	int getCount() const;        // Added by Rebal
	void print() const;          // Added by Rebal

	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~LinkedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);

	if (isEmpty())
		frontPtr = newNodePtr;
	else
		backPtr->setNext(newNodePtr);

	backPtr = newNodePtr;
	count++;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	if (nodeToDeletePtr == backPtr)
		backPtr = nullptr;

	delete nodeToDeletePtr;
	count--;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;
	while (dequeue(temp));
}

///////////////////////////////////////////////////////////////////////////////////
// FIXED: Added missing copy constructor implementation

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr)
	{
		frontPtr = backPtr = nullptr;
		count = 0;
		return;
	}

	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
	count = LQ.count;
}

///////////////////////////////////////////////////////////////////////////////////

template <typename T>
int LinkedQueue<T>::getCount() const
{
	return count;
}

template <typename T>
void LinkedQueue<T>::print() const
{
	Node<T>* curr = frontPtr;
	if (!curr) {
		cout << "Empty" << endl;
		return;
	}
	while (curr) {
		cout << curr->getItem() << " ";
		curr = curr->getNext();
	}
	cout << endl;
}

#endif