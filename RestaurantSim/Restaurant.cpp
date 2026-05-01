#include "Restaurant.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Restaurant::Restaurant() {
    pendingOrders = new Queue<Order*>();
    cookingOrders = new CookingQueue();
    readyOrders = new Queue<Order*>();
    inServiceOrders = new priQueue<Order*>();
    finishedOrders = new Queue<Order*>();
    cancelledOrders = new Queue<Order*>();
    freeScooters = new priQueue<Scooter*>();
    backScooters = new priQueue<Scooter*>();
    maintScooters = new Queue<Scooter*>();

    pUI = nullptr; // Add this line
}
Restaurant::~Restaurant() {
    delete pendingOrders;
    delete cookingOrders;
    delete readyOrders;
    delete inServiceOrders;
    delete finishedOrders;
    delete cancelledOrders;
    delete freeScooters;
    delete backScooters;
    delete maintScooters;
}
void Restaurant::RunSimulation()
{
    std::cout << "Running simulation..." << std::endl;
    srand((unsigned int)time(0));
    for (int i = 1; i <= 500; i++)
    {
        Order* newOrder = new Order(i, OVN, 2, 100, 1);
        pendingOrders->enqueue(newOrder);
    }
    int timestep = 1;
    bool simulationDone = false;
    while (!simulationDone)
    {
        for (int i = 0; i < 30; i++)
        {
            if (!pendingOrders->isEmpty())
            {
                Order* o = pendingOrders->dequeue();
                int dummyPriority = rand() % 100;
                cookingOrders->enqueue(o, dummyPriority);
            }
        }
        int randomIDToCancel = (rand() % 500) + 1;
        bool isCancelled = cookingOrders->CancelOrder(randomIDToCancel);
        if (isCancelled)
        {
        }

        if (!cookingOrders->isEmpty()) {
            int toServiceChance = rand() % 100;
            if (toServiceChance < 30) {
                int pri;
                Order* readyOrder;
                if (cookingOrders->dequeue(readyOrder, pri)) {
                    readyOrder->resourceType = (rand() % 2 == 0) ? 'S' : 'T';
                    readyOrder->resourceID = (rand() % 20) + 1;
                    readyOrder->finishTime = timestep + 10;
                    inServiceOrders->enqueue(readyOrder, (100000 - readyOrder->finishTime));
                }
            }
        }

        int finishChance = rand() % 100;
        if (finishChance < 25 && !inServiceOrders->isEmpty()) {
            Order* finishedOrder;
            int pri;
            inServiceOrders->dequeue(finishedOrder, pri);
            finishedOrders->enqueue(finishedOrder);

            Scooter* dummyScooter = new Scooter((rand() % 100), 20, 5, 5);
            int maintChance = rand() % 100;
            if (maintChance < 50) {
                maintScooters->enqueue(dummyScooter);
            }
            else {
                backScooters->enqueue(dummyScooter, 10);
            }
        }
        if (pendingOrders->isEmpty() && cookingOrders->isEmpty() &&
            readyOrders->isEmpty() && inServiceOrders->isEmpty()) {
            simulationDone = true;
        }

        cout << "Timestep: " << timestep << endl;
        int inServiceCount = inServiceOrders->GetCount();
        cout << "In-Service orders [order ID, scooter/Table ID]" << endl;
        cout << inServiceCount << " Orders: ";
        inServiceOrders->print();
        cout << endl << "-------------------------------------------" << endl;

        timestep++;
    }
}

// =========================================================================
// --- Implementation of missing Action functions ---
// =========================================================================

void Restaurant::addPendingODG(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingODN(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOT(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVG(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVC(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVN(Order* pOrd) { pendingOrders->enqueue(pOrd); }

bool Restaurant::RemoveFromPendingOVC(int id) {
    // Basic implementation for compilation
    return false;
}

bool Restaurant::RemoveFromCookingOVC(int id) {
    // Calls the CancelOrder logic already in your CookingQueue
    return cookingOrders->CancelOrder(id);
}

bool Restaurant::RemoveFromReadyOVC(int id) {
    return false;
}

void Restaurant::ReleaseChefFromOrder(int id) {
    // Placeholder for future Chef module logic
}