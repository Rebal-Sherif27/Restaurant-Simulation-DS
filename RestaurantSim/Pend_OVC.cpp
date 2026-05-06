#include "Pend_OVC.h"
using namespace std;

bool Pend_OVC::CancelOrder(int id) {
    LinkedQueue<Order*> tempQueue;
    bool found = false;
    Order* currentOrder;

    // Empty this queue into the temp queue, looking for the ID
    while (!this->isEmpty()) {
        this->dequeue(currentOrder);
        if (currentOrder->id == id) {
            found = true;
        }
        else {
            tempQueue.enqueue(currentOrder);
        }
    }

    // Put everything back
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(currentOrder);
        this->enqueue(currentOrder);
    }

    return found;
}