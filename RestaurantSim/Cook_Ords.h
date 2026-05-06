#pragma once
#include "priQueue.h"
#include "Order.h"

class Cook_Ords : public priQueue<Order*> {
public:
    // Searches for the order by ID and removes it from the cooking queue
    bool CancelOrder(int id);
};