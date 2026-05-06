#include "Cook_Ords.h"
using namespace std;

bool Cook_Ords::CancelOrder(int id) {
    priQueue<Order*> tempQueue;
    bool found = false;
    Order* currentOrder;
    int currentPriority;

    // 1. Empty this priority queue into a temporary one, searching for the ID
    while (!this->isEmpty()) {
        this->dequeue(currentOrder, currentPriority);

        if (currentOrder->id == id) {
            found = true; // Found it! We don't put it in tempQueue, effectively removing it.
        }
        else {
            tempQueue.enqueue(currentOrder, currentPriority);
        }
    }

    // 2. Put everything back into the original cooking queue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(currentOrder, currentPriority);
        this->enqueue(currentOrder, currentPriority);
    }

    return found;
}