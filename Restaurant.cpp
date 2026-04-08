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
    // ... rest of your code remains exactly the same ...