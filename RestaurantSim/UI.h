#pragma once
#include "Order.h"
#include "Queue.h"
#include "priQueue.h"
#include "FinishedOrders.h"
class UI
{
public:
    void WaitForKey();
    int getMode();
    void PrintPhase1Screen(int timestep,
        Queue<Order*>* pending,
        Queue<Order*>* ready,
        priQueue<Order*>* service,
        FinishedOrders* finished);
};