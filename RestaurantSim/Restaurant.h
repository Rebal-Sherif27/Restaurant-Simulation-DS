#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "FinishedOrders.h"
#include "Order.h"
#include "Scooter.h"
#include "Queue.h"
#include "priQueue.h"
#include "CookingQueue.h"
#include "UI.h"
#include "Table.h"
#include "Action.h"   
#include "Chef.h"
class UI;

class Restaurant {
private:
    Queue<Action*>* actionsList;
    Queue<Order*>* pendingODG;
    Queue<Order*>* pendingODN;
    Queue<Order*>* pendingOT;
    Queue<Order*>* pendingOVG;
    Queue<Order*>* pendingOVC;
    Queue<Order*>* pendingOVN;

    Queue<Chef*>* freeCS;
    Queue<Chef*>* freeCN;

    // --- Existing lists ---
    Queue<Order*>* pendingOrders;      
    CookingQueue* cookingOrders;
    Queue<Order*>* readyOrders;
    priQueue<Order*>* inServiceOrders;
    FinishedOrders* finishedOrders;
    Queue<Order*>* cancelledOrders;

    priQueue<Scooter*>* freeScooters;
    priQueue<Scooter*>* backScooters;
    Queue<Scooter*>* maintScooters;

    Queue<Table*>* freeTables;
    Queue<Table*>* reservedTables;
    Queue<Table*>* sharableTables;
    Queue<Table*>* occupiedTables;

    UI* pUI;

    int TH;   // overwait threshold

public:
    Restaurant();
    ~Restaurant();

    void RunSimulation();
    void LoadFromFile(string filename);
    void ExecuteActionsAtTime(int currentTime);
    void CancelOrder(int orderID);
    void GenerateOutputFile(); 

    // --- Existing getters  ---
    Queue<Order*>* getPendingOrders() const { return pendingOrders; }
    CookingQueue* getCookingOrders() const { return cookingOrders; }
    Queue<Order*>* getReadyOrders() const { return readyOrders; }
    priQueue<Order*>* getInServiceOrders() const { return inServiceOrders; }
    FinishedOrders* getFinishedOrders() const { return finishedOrders; }
    Queue<Order*>* getCancelledOrders() const { return cancelledOrders; }

    priQueue<Scooter*>* getFreeScooters() const { return freeScooters; }
    priQueue<Scooter*>* getBackScooters() const { return backScooters; }
    Queue<Scooter*>* getMainScooters() const { return maintScooters; }

    // --- Existing action functions  ---
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
    void FreeFinishedTables(int timestep);
    void AssignTable(int timestep);

    void AssignPendingToChef(int currentTime);
    void MoveCookingToReady(int currentTime);
    void FinalizeTakeawayOrders(int currentTime);
};

#endif

