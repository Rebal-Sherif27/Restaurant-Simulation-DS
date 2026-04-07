#pragma once
#pragma once
#include "Queue.h"
#include "Order.h"
#include <iostream>
using namespace std;

class Restaurant {
private:
    // Pending lists (6 types)
    Queue<Order*> pendingODG;
    Queue<Order*> pendingODN;
    Queue<Order*> pendingOT;
    Queue<Order*> pendingOVG;
    Queue<Order*> pendingOVC;
    Queue<Order*> pendingOVN;

    // Cooking lists
    Queue<Order*> cookingOVC;

    // Ready lists
    Queue<Order*> readyOVC;

    // Cancelled orders storage
    Queue<int> cancelledOrders;

    int currentTime;

public:
    Restaurant();
    ~Restaurant();

    // Add to pending lists
    void addPendingODG(Order* o);
    void addPendingODN(Order* o);
    void addPendingOT(Order* o);
    void addPendingOVG(Order* o);
    void addPendingOVC(Order* o);
    void addPendingOVN(Order* o);

    // Remove from OVC lists for cancellation
    bool RemoveFromPendingOVC(int orderID);
    bool RemoveFromCookingOVC(int orderID);
    bool RemoveFromReadyOVC(int orderID);

    // Release chef when order cancelled from cooking
    void ReleaseChefFromOrder(int orderID);

    // Random generation for Phase 1.2
    void GenerateRandomPendingOrders(int count);

    // Print all lists (for Phase 1.2)
    void PrintAllLists();

    // Getters for UI
    Queue<Order*>* getPendingODG() { return &pendingODG; }
    Queue<Order*>* getPendingODN() { return &pendingODN; }
    Queue<Order*>* getPendingOT() { return &pendingOT; }
    Queue<Order*>* getPendingOVG() { return &pendingOVG; }
    Queue<Order*>* getPendingOVC() { return &pendingOVC; }
    Queue<Order*>* getPendingOVN() { return &pendingOVN; }
    Queue<int>* getCancelledOrders() { return &cancelledOrders; }
};
// Getters for your lists
Queue<Order*>* getPendingODG() { return &pendingODG; }
Queue<Order*>* getPendingODN() { return &pendingODN; }
Queue<Order*>* getPendingOT() { return &pendingOT; }
Queue<Order*>* getPendingOVG() { return &pendingOVG; }
Queue<Order*>* getPendingOVC() { return &pendingOVC; }
Queue<Order*>* getPendingOVN() { return &pendingOVN; }
Queue<Order*>* getReadyOVC() { return &readyOVC; }
Queue<int>* getCancelledOrders() { return &cancelledOrders; }
