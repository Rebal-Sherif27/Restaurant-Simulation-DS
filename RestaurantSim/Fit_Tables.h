#pragma once
#include "priQueue.h"
#include "Table.h"

class Fit_Tables : public priQueue < Table* >
{
    Table* getBest()
    {
        while (!isEmpty())
        {
            Table *best;
            int p;
            peek(best, p);
            if (best->getCapacity() >= best->getCurrentload())
                return best;
            else
                dequeue(best, p); // Remove tables that can't fit the order
        }
    }
};

