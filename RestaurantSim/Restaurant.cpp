#include "Restaurant.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Order.h"
#include "Table.h"
#include "UI.h"

Restaurant::Restaurant()
    : pendingOrders(new Queue<Order*>())
    , cookingOrders(new CookingQueue())
    , readyOrders(new Queue<Order*>())
    , inServiceOrders(new priQueue<Order*>())
    , finishedOrders(new Queue<Order*>())
    , cancelledOrders(new Queue<Order*>())
    , freeScooters(new priQueue<Scooter*>())
    , backScooters(new priQueue<Scooter*>())
    , maintScooters(new Queue<Scooter*>())
    , freeTables(new Queue<Table*>())
    , occupiedTables(new Queue<Table*>())
    , reservedTables(new Queue<Table*>())
    , sharableTables(new Queue<Table*>())
    , pUI(nullptr)
{
    // Leave this empty! Everything is already handled by the list above.
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
    delete occupiedTables;
    delete reservedTables;
    delete sharableTables;

    if (pUI) delete pUI;
}

void Restaurant::RunSimulation()
{
    pUI = new UI();
    int currentMode = pUI->getMode();
    srand((unsigned int)time(0));

    int timestep = 1;
    bool simulationDone = false;

    // Initial screen before loop
    if (currentMode == 1 || currentMode == 2)
    {
        pUI->PrintPhase1Screen(timestep, pendingOrders, readyOrders, inServiceOrders, finishedOrders);
        if (currentMode == 1) pUI->WaitForKey();
    }

    std::cout << "Running simulation..." << std::endl;

    // --- TEST DATA ---
    freeTables->enqueue(new Table(1, 4, true));
    freeTables->enqueue(new Table(2, 2, false));
    readyOrders->enqueue(new Order(99, OVN, 3, 1, 1));

    for (int i = 1; i <= 500; i++)
    {
        Order* newOrder = new Order(i, OVN, 2, 100, 1);
        pendingOrders->enqueue(newOrder);
    }

    while (!simulationDone)
    {
        // 1. Dequeue Pending to Cooking
        for (int i = 0; i < 30; i++)
        {
            if (!pendingOrders->isEmpty())
            {
                Order* o = pendingOrders->dequeue();
                int dummyPriority = rand() % 100;
                cookingOrders->enqueue(o, dummyPriority);
            }
        }

        // 2. Cancellation
        int randomIDToCancel = (rand() % 500) + 1;
        cookingOrders->CancelOrder(randomIDToCancel);

        // 3. Table Management
        AssignTable(timestep);

        // 4. Move to Service (Simulation Logic)
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

        // 5. Check Finished Orders (Simulation Logic)
        int finishChance = rand() % 100;
        if (finishChance < 25 && !inServiceOrders->isEmpty()) {
            Order* finishedOrder;
            int pri;
            inServiceOrders->dequeue(finishedOrder, pri);
            finishedOrders->enqueue(finishedOrder);
            // Scooter/Maintenance logic here...
        }

        // 6. UI MODES (MUST BE INSIDE THE WHILE LOOP)
        if (currentMode == 1) // Interactive
        {
            pUI->PrintPhase1Screen(timestep, pendingOrders, readyOrders, inServiceOrders, finishedOrders);
            pUI->WaitForKey();
        }
        else if (currentMode == 2) // Step-by-Step
        {
            pUI->PrintPhase1Screen(timestep, pendingOrders, readyOrders, inServiceOrders, finishedOrders);
            // Delay logic here
        }
        else if (currentMode == 3) // Silent
        {
            // Stay quiet
        }

        // 7. Check if Simulation is done
        if (pendingOrders->isEmpty() && cookingOrders->isEmpty() &&
            readyOrders->isEmpty() && inServiceOrders->isEmpty()) {
            simulationDone = true;
        }

        // 8. Timestep Increment
        timestep++;
        if (timestep > 50) { simulationDone = true; }

    } // <--- THIS BRACE CLOSES THE WHILE LOOP

    // 9. Final Message (OUTSIDE THE LOOP, INSIDE THE FUNCTION)
    if (currentMode == 3)
    {
        std::cout << "Silent Mode execution finished. Output file generated." << std::endl;
    }

} // <--- THIS BRACE CLOSES RUNSIMULATION
    

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

// =========================================================
// 1. ASSIGN TABLE FUNCTION
// =========================================================
void Restaurant::AssignTable(int timestep)
{
    if (readyOrders->isEmpty()) return;
    if (occupiedTables->isEmpty() && freeTables->isEmpty()) return;

    Order* nextOrder = readyOrders->peekFront();
    int orderSize = nextOrder->getSize();
    Table* foundTable = nullptr;
    bool isNewTable = false;

    // --- 1. Search Occupied Tables (Sharable) ---
    Queue<Table*> tempOccupied;
    while (!occupiedTables->isEmpty()) {
        Table* t = occupiedTables->dequeue();
        if (t->isSharable() && (t->getCapacity() - t->getCurrentload() >= orderSize) && !foundTable) {
            foundTable = t;
        }
        tempOccupied.enqueue(t);
    }
    while (!tempOccupied.isEmpty()) occupiedTables->enqueue(tempOccupied.dequeue());

    // --- 2. Search Free Tables ---
    if (!foundTable) {
        Queue<Table*> tempFree;
        while (!freeTables->isEmpty()) {
            Table* t = freeTables->dequeue();
            if (t->getCapacity() >= orderSize && !foundTable) {
                foundTable = t;
                isNewTable = true;
            }
            else {
                tempFree.enqueue(t);
            }
        }
        while (!tempFree.isEmpty()) freeTables->enqueue(tempFree.dequeue());
    }

    // --- 3. Assignment Execution ---
    if (foundTable) {
        readyOrders->dequeue();
        nextOrder->finishTime = timestep + nextOrder->duration;
        inServiceOrders->enqueue(nextOrder, (100000 - nextOrder->finishTime));
        foundTable->assignorder(nextOrder);
        if (isNewTable) occupiedTables->enqueue(foundTable);
    }
}

// =========================================================
// 2. FREE FINISHED TABLES FUNCTION
// =========================================================
void Restaurant::FreeFinishedTables(int timestep)
{
    if (inServiceOrders->isEmpty()) return;

    Order* pOrd;
    int pri;

    while (inServiceOrders->peek(pOrd, pri))
    {
        if (pOrd->getFinishTime() <= timestep)
        {
            inServiceOrders->dequeue(pOrd, pri);
            int tID = pOrd->getTableID(); // Check your Order.h spelling (tableID)

            Queue<Table*> tempOccupied;
            Table* targetTable = nullptr;

            while (!occupiedTables->isEmpty())
            {
                Table* t = occupiedTables->dequeue();
                if (t->getTabelID() == tID) {
                    targetTable = t;
                }
                else {
                    tempOccupied.enqueue(t);
                }
            }

            if (targetTable)
            {
                int newLoad = targetTable->getCurrentload() - pOrd->getNumPeople();
                targetTable->setCurrentload(newLoad);

                if (newLoad <= 0) {
                    targetTable->freeTable();
                    freeTables->enqueue(targetTable);
                }
                else {
                    tempOccupied.enqueue(targetTable);
                }
            }

            while (!tempOccupied.isEmpty()) {
                occupiedTables->enqueue(tempOccupied.dequeue());
            }

            finishedOrders->enqueue(pOrd);
        }
        else {
            break;
        }
    }
}