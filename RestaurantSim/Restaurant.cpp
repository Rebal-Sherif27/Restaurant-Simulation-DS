#include "Restaurant.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    pUI = nullptr;
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
        {   }
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
        timestep++;
    }
    std::cout << "Simulation Finished! Total Timesteps taken: " << timestep << std::endl;
}

// =========================================================================
// --- Missing Action Implementations (Added to resolve ActionList calls) ---
// =========================================================================

void Restaurant::addPendingODG(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingODN(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOT(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVG(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVC(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVN(Order* pOrd) { pendingOrders->enqueue(pOrd); }

bool Restaurant::RemoveFromPendingOVC(int id) {
    // TODO: Implement search and remove logic for your standard Queue
    // Returning false for now so the program compiles.
    return false;
}

bool Restaurant::RemoveFromCookingOVC(int id) {
    // Uses the CancelOrder method already built into your CookingQueue
    return cookingOrders->CancelOrder(id);
}

bool Restaurant::RemoveFromReadyOVC(int id) {
    // TODO: Implement search and remove logic for your standard Queue
    return false;
}

void Restaurant::ReleaseChefFromOrder(int id) {
    // TODO: Implement chef release logic once Chefs are fully implemented
}