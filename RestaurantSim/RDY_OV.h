#pragma once
#include "LinkedQueue.h"
#include "Order.h"

class RDY_OV : public LinkedQueue<Order*>
{
public:
    // This declares the cancellation function so the .cpp file can use it
    bool CancelOrder(int id);
};