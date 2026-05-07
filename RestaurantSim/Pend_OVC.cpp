#include "Pend_OVC.h"
using namespace std;

bool Pend_OVC::CancelOrder(int id) {
    LinkedQueue<Order*> tempQueue;
    bool found = false;
    Order* currentOrder;

    while (!this->isEmpty()) {
        this->dequeue(currentOrder);
        if (currentOrder->id == id) {
            found = true;
        }
        else {
            tempQueue.enqueue(currentOrder);
        }
    }

    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(currentOrder);
        this->enqueue(currentOrder);
    }

    return found;
}