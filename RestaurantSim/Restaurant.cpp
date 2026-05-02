#include "Restaurant.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Order.h"
#include "Table.h"
#include "UI.h"

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
    freeTables = new Queue<Table*>();

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
    delete freeTables;
}
void Restaurant::RunSimulation()
{
    pUI = new UI();
    int currentMode = pUI->getMode();

    std::cout << "Running simulation..." << std::endl;

    srand((unsigned int)time(0));

    // --- ADDITION 1: TEST DATA ---
    // Populate some tables so AssignTable has something to use
    freeTables->enqueue(new Table(1, 4, true));
    freeTables->enqueue(new Table(2, 2, false));
    // Spawn one ready order to test the movement
    readyOrders->enqueue(new Order(99, OVN, 3, 1, 1));
    // ----------------------------

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

        // --- ADDITION 2: CALL YOUR FUNCTION ---
        AssignTable(timestep);
        // --------------------------------------

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

        if (currentMode == 1) // Interactive Mode
        {
            pUI->PrintPhase1Screen(timestep);
            pUI->WaitForKey();
        }

        else if (currentMode == 2) // Step-by-Step Mode
        {
            pUI->PrintPhase1Screen(timestep);
            // We will add a 1-second delay here later
        }

        else if (currentMode == 3) // Silent Mode
        {
            // Do not print anything during the loop
        }

        cout << "Timestep: " << timestep << endl;
        int inServiceCount = inServiceOrders->GetCount();
        cout << "In-Service orders [order ID, scooter/Table ID]" << endl;
        cout << inServiceCount << " Orders: ";
        inServiceOrders->print();
        cout << endl << "-------------------------------------------" << endl;

        timestep++;

        if (timestep > 50) 
        {
            simulationDone = true;
        }
        // --- ADDITION 3: MOVE MESSAGE OUTSIDE LOOP ---
        if (currentMode == 3) {
            std::cout << "Silent Mode execution finished. Output file generated." << std::endl;
        }
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

void Restaurant::AssignTable(int timestep)
{
    // 1. Are there any Dine-In orders ready to be seated?
    if (readyOrders->isEmpty()) {
        return; // No one is waiting for a table, do nothing.
    }

    // 2. Peek at the next order in the line
    Order* nextOrder = readyOrders->peekFront();

    int orderSize = nextOrder->getSize();

    Table* foundTable = nullptr;
    bool isNewTable = false;

    // =========================================================
    // 1. SEARCH OCCUPIED TABLES (For Sharable space)
    // =========================================================

    if (!occupiedTables->isEmpty()) 
    {
        Table* t = occupiedTables->peekFront();
        occupiedTables->dequeue();
        // Check if this table can accommodate the new order
        if (t->isSharable() && (t->getCapacity() - t->getCurrentload() >= orderSize)) 
        {
            foundTable = t;
            isNewTable = false;
        }
        else 
        {
            occupiedTables->enqueue(t); // Put it back if it can't accommodate
        }
    }
    // =========================================================
    // 2. SEARCH FREE TABLES (If no sharable table worked)
    // =========================================================
    if (!foundTable) {
        Queue<Table*> tempFree;
        while (!freeTables->isEmpty()) {
            Table* t = freeTables->dequeue();

            if (t->getCapacity() >= orderSize && foundTable == nullptr) {
                foundTable = t;
                isNewTable = true; // Mark that we took this from the free list
            }
            else {
                tempFree.enqueue(t); // Only put it back if we DIDN'T choose it
            }
        }
        // Put the unused free tables back
        while (!tempFree.isEmpty()) {
            Table* t = tempFree.dequeue();
            freeTables->enqueue(t);
        }
    }
    // =========================================================
    // 3. ASSIGN THE TABLE AND MOVE THE ORDER
    // =========================================================
    
    if(foundTable) 
    {
        // remove the order from ready queue (we already peeked it)
        readyOrders->dequeue();
        nextOrder->finishTime = timestep + nextOrder->duration; // Set expected finish time
        inServiceOrders->enqueue(nextOrder, (100000 - nextOrder->finishTime)); // Move to in-service with priority
        foundTable->assignorder(nextOrder); // Assign the order to the table
        if (isNewTable) 
        {
            occupiedTables->enqueue(foundTable); // Move to occupied if it was free
        }
    }
}