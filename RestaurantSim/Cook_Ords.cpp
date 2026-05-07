#include "Cook_Ords.h"
using namespace std;

bool Cook_Ords::CancelOrder(int id) {
    priQueue<Order*> tempQueue;
    bool found = false;
    Order* currentOrder;
    int currentPriority;

    
    while (!this->isEmpty()) {
        this->dequeue(currentOrder, currentPriority);

        if (currentOrder->id == id) {
            found = true; 
        }
        else {
            tempQueue.enqueue(currentOrder, currentPriority);
        }
    }

    
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(currentOrder, currentPriority);
        this->enqueue(currentOrder, currentPriority);
    }

    return found;
}