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

    pUI = nullptr; // FIXED: pUI uninitialized warning
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

// Ensure these lines exist at the bottom of your Restaurant.cpp
void Restaurant::addPendingODG(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingODN(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOT(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVG(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVC(Order* pOrd) { pendingOrders->enqueue(pOrd); }
void Restaurant::addPendingOVN(Order* pOrd) { pendingOrders->enqueue(pOrd); }

bool Restaurant::RemoveFromPendingOVC(int id) { return false; }
bool Restaurant::RemoveFromCookingOVC(int id) { return cookingOrders->CancelOrder(id); }
bool Restaurant::RemoveFromReadyOVC(int id) { return false; }
void Restaurant::ReleaseChefFromOrder(int id) { /* TODO */ }

void Restaurant::RunSimulation() {
    // Your simulation code should be here
}
    // ... rest of your code remains exactly the same ...