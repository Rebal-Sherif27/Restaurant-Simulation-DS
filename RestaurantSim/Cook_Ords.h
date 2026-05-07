#pragma once
#include "priQueue.h"
#include "Order.h"

class Cook_Ords : public priQueue<Order*> {
public:
    bool CancelOrder(int id);
};