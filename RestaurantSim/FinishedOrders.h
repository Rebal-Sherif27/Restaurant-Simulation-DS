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

        // 1. Pop from main stack, print, and save to temp stack
        while (this->pop(pOrd)) {
            std::cout << pOrd->id << " ";
            tempStack.push(pOrd);
        }

        // 2. Put everything back so the data isn't lost
        while (tempStack.pop(pOrd)) {
            this->push(pOrd);
        }
    }
};