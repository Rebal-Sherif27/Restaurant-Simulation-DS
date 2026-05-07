#pragma once
#ifndef COOKINGQUEUE_H
#define COOKINGQUEUE_H

#include "PriQueue.h" 
#include "Order.h"
class CookingQueue : public priQueue<Order*>
{
public:

    bool CancelOrder(int cancelID)
    {
        if (this->isEmpty())
        {
            return false;
        }

        int dummyPri;

        if (head->getItem(dummyPri)->id == cancelID)
        {
            priNode<Order*>* temp = head;
            head = head->getNext();
            delete temp;
            count--;
            return true;
        }

        priNode<Order*>* current = head;

        while (current->getNext() != nullptr)
        {
            if (current->getNext()->getItem(dummyPri)->id == cancelID)
            {
                priNode<Order*>* nodeToDelete = current->getNext();
                current->setNext(nodeToDelete->getNext());
                delete nodeToDelete;
                count--;
                return true;
            }

            current = current->getNext();
        }

        return false;
    }
};
#endif
