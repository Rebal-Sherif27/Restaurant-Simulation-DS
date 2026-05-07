#pragma once
#include "LinkedQueue.h"
#include "Order.h"

class RDY_OV : public LinkedQueue<Order*>
{
public:
    bool CancelOrder(int id);
};