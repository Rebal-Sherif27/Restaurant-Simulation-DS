#pragma once
#include "priQueue.h"
#include "Table.h"

class Fit_Tables : public priQueue < Table* >
{
    Table* getBest()
    {   
        priQueue<Table*> tempQueue;  // 1. Create a local temporary queue
        Table* foundTable = nullptr;

        while (!isEmpty())
        {
            Table *best;
            int p;
            peek(best, p);
            if (best->getCapacity() >= best->getCurrentload())
                return best;
            else
            tempQueue.enqueue(best, p); // Reinsert the table to maintain the priority order
        }
        // Restore the original queue
        while (!tempQueue.isEmpty()) {
            Table* t;
            int p;
            tempQueue.dequeue(t, p);
            this->enqueue(t, p);
        }
        return foundTable;
    }
};

