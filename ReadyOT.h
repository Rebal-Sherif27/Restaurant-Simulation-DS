#pragma once
#include "LinkedQueue.h"

class Order;

class ReadyOT : public LinkedQueue<Order*>
{
public:
    ReadyOT() {}
};