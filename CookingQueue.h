#pragma once
#ifndef COOKINGQUEUE_H
#define COOKINGQUEUE_H

#include "priQueue.h" 
#include "Order.h"

class CookingQueue : public priQueue<Order*>
{
public:
	// Changed to return Order* instead of bool
	Order* CancelOrder(int cancelID)
	{
		if (this->isEmpty()) {
			return nullptr;
		}
		int dummyPri;

		// 1. Check if the order to cancel is at the head
		if (head->getItem(dummyPri)->id == cancelID)
		{
			priNode<Order*>* temp = head;
			head = head->getNext();
			Order* cancelledOrder = temp->getItem(dummyPri);
			delete temp;
			return cancelledOrder;
		}

		// 2. Search the rest of the queue
		priNode<Order*>* current = head;
		while (current->getNext() != nullptr) {
			if (current->getNext()->getItem(dummyPri)->id == cancelID) {
				priNode<Order*>* nodeToDelete = current->getNext();

				// Fix: Rewire the linked list to skip the deleted node
				current->setNext(nodeToDelete->getNext());

				Order* cancelledOrder = nodeToDelete->getItem(dummyPri);
				delete nodeToDelete;
				return cancelledOrder;
			}
			current = current->getNext();
		}
		return nullptr;
	}
};
#endif