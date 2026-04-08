#pragma once
#include "ArrayStack.h"

class Order;

class FinishedOrders : public ArrayStack<Order*>
{
public:
    FinishedOrders(){}
};