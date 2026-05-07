#pragma once
#include "ArrayStack.h"
#include "Order.h"
#include <iostream>

class FinishedOrders : public ArrayStack<Order*>
{
public:
    FinishedOrders() {}

    void printIDs() {
        ArrayStack<Order*> tempStack;
        Order* pOrd;

        while (this->pop(pOrd)) {
            std::cout << pOrd->id << " ";
            tempStack.push(pOrd);
        }

        while (tempStack.pop(pOrd)) {
            this->push(pOrd);
        }
    }
};