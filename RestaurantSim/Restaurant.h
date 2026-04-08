#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Order.h"
#include "Scooter.h"
#include "Queue.h"
#include "priQueue.h"
#include "CookingQueue.h"

class UI;

class Restaurant {
private:
    Queue<Order*>* pendingOrders;     
    CookingQueue* cookingOrders;      
    Queue<Order*>* readyOrders;        
    priQueue<Order*>* inServiceOrders; 
    Queue<Order*>* finishedOrders;   
    Queue<Order*>* cancelledOrders;

    priQueue<Scooter*>* freeScooters;
    priQueue<Scooter*>* backScooters;
    Queue<Scooter*>* maintScooters;

    UI* pUI;
public:
    Restaurant();
~Restaurant();

void RunSimulation();

Queue<Order*>* getPendingOrders() const { return pendingOrders; }
CookingQueue* getCookingOrders() const { return cookingOrders; }
Queue<Order*>* getReadyOrders() const { return readyOrders; }
priQueue<Order*>* getInServiceOrders() const { return inServiceOrders; }
Queue<Order*>* getFinishedOrders() const { return finishedOrders; }
Queue<Order*>* getCancelledOrders() const { return cancelledOrders; }

priQueue<Scooter*>* getFreeScooters() const { return freeScooters; }
priQueue<Scooter*>* getBackScooters() const { return backScooters; }
Queue<Scooter*>* getMainScooters() const { return maintScooters; }

// --- Missing Action Functions ---
void addPendingODG(Order* pOrd);
void addPendingODN(Order* pOrd);
void addPendingOT(Order* pOrd);
void addPendingOVG(Order* pOrd);
void addPendingOVC(Order* pOrd);
void addPendingOVN(Order* pOrd);

bool RemoveFromPendingOVC(int id);
bool RemoveFromCookingOVC(int id);
bool RemoveFromReadyOVC(int id);
void ReleaseChefFromOrder(int id);

};
#endif

