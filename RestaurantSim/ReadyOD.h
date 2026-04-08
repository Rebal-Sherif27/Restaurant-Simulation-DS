#pragma once
#include"LinkedQueue.h"

class Order;

class ReadyOD : public LinkedQueue<Order*>
{
public:
    ReadyOD(){}
};