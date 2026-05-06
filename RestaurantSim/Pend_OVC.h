#pragma once
#include "LinkedQueue.h"
#include "Order.h"
using namespace std;

class Pend_OVC : public LinkedQueue<Order*>
{
public:
    bool CancelOrder(int id);
};

