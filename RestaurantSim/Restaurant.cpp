#include "Restaurant.h"
#include "RequestAction.h"
#include "CancelAction.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ==================== CONSTRUCTOR / DESTRUCTOR (merged) ====================
Restaurant::Restaurant()
    : cookingOrders(new CookingQueue())
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
    // Your new lists
    actionsList = new Queue<Action*>();
    pendingODG = new Queue<Order*>();
    pendingODN = new Queue<Order*>();
    pendingOT = new Queue<Order*>();
    pendingOVG = new Queue<Order*>();
    pendingOVC = new Queue<Order*>();
    pendingOVN = new Queue<Order*>();
    TH = 0;

    // Keep old pendingOrders (optional, for backward compatibility)
    pendingOrders = new Queue<Order*>();
}

Restaurant::~Restaurant() {
    delete actionsList;
    delete pendingODG; delete pendingODN; delete pendingOT;
    delete pendingOVG; delete pendingOVC; delete pendingOVN;
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

// ==================== YOUR NEW FUNCTIONS (Features 2,3,7) ====================
void Restaurant::LoadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    int numCN, numCS, speedCN, speedCS, numScooters, scooterSpeed, maintOrds, maintDur;
    file >> numCN >> numCS;
    file >> speedCN >> speedCS;
    file >> numScooters >> scooterSpeed;
    file >> maintOrds >> maintDur;
    int totalTables;
    file >> totalTables;
    for (int i = 0; i < totalTables; i++) {
        int tableCount, capacity;
        file >> tableCount >> capacity;
        for (int j = 0; j < tableCount; j++) {
            freeTables->enqueue(new Table(capacity, capacity, true));
        }
    }
    file >> TH;
    int M;
    file >> M;
    for (int i = 0; i < M; i++) {
        char type;
        file >> type;
        if (type == 'Q') {
            string orderType;
            int t, id, size, price, seats, duration, dist;
            char shareChar;
            file >> orderType >> t >> id >> size >> price;
            if (orderType == "ODG" || orderType == "ODN") {
                file >> seats >> duration >> shareChar;
                bool canShare = (shareChar == 'Y');
                actionsList->enqueue(new RequestAction(t, orderType, id, size, price, seats, duration, canShare, 0));
            }
            else if (orderType == "OT") {
                actionsList->enqueue(new RequestAction(t, orderType, id, size, price, 0, 0, false, 0));
            }
            else {
                file >> dist;
                actionsList->enqueue(new RequestAction(t, orderType, id, size, price, 0, 0, false, dist));
            }
        }
        else if (type == 'X') {
            int t, id;
            file >> t >> id;
            actionsList->enqueue(new CancelAction(t, id));
        }
    }
    file.close();
}

void Restaurant::ExecuteActionsAtTime(int currentTime) {
    while (!actionsList->isEmpty()) {
        Action* act = actionsList->peekFront();
        if (act->GetActionTime() == currentTime) {
            actionsList->dequeue();
            act->Execute(this);
        }
        else {
            break;
        }
    }
}

void Restaurant::CancelOrder(int orderID) {
    if (RemoveFromPendingOVC(orderID)) return;
    if (RemoveFromCookingOVC(orderID)) return;
    RemoveFromReadyOVC(orderID);
}

// ==================== RUN SIMULATION (YOUR NEW VERSION) ====================
void Restaurant::RunSimulation() {
    pUI = new UI();
    int mode = pUI->getMode();
    LoadFromFile("input.txt");   // Feature 2

    int currentTime = 0;
    bool done = false;

    while (!done) {
        ExecuteActionsAtTime(currentTime);   // Feature 3
        FreeFinishedTables(currentTime);      // Feature 7 (existing function, kept)
        AssignTable(currentTime);             // existing function

        // Chef assignment and scooter assignment will be added here by Shahd and Ali

        if (mode == 1) {
            // Note: PrintPhase1Screen expects pendingOrders (old). For now we pass pendingODG as placeholder.
            pUI->PrintPhase1Screen(currentTime, pendingODG, readyOrders, inServiceOrders, finishedOrders);
            pUI->WaitForKey();
        }

        currentTime++;
        if (actionsList->isEmpty() &&
            pendingODG->isEmpty() && pendingODN->isEmpty() &&
            pendingOT->isEmpty() && pendingOVG->isEmpty() &&
            pendingOVC->isEmpty() && pendingOVN->isEmpty() &&
            cookingOrders->isEmpty() && readyOrders->isEmpty() &&
            inServiceOrders->isEmpty()) {
            done = true;
        }
    }

    if (mode == 3) {
        cout << "Silent Mode execution finished. Output file generated." << endl;
    }
    delete pUI;
    pUI = nullptr;
}

// ==================== EXISTING FUNCTIONS (kept exactly as you had) ====================
void Restaurant::addPendingODG(Order* pOrd) { pendingODG->enqueue(pOrd); }
void Restaurant::addPendingODN(Order* pOrd) { pendingODN->enqueue(pOrd); }
void Restaurant::addPendingOT(Order* pOrd) { pendingOT->enqueue(pOrd); }
void Restaurant::addPendingOVG(Order* pOrd) { pendingOVG->enqueue(pOrd); }
void Restaurant::addPendingOVC(Order* pOrd) { pendingOVC->enqueue(pOrd); }
void Restaurant::addPendingOVN(Order* pOrd) { pendingOVN->enqueue(pOrd); }

bool Restaurant::RemoveFromPendingOVC(int id) {
    Queue<Order*> temp;
    bool found = false;
    while (!pendingOVC->isEmpty()) {
        Order* o = pendingOVC->dequeue();
        if (o->id == id) {
            cancelledOrders->enqueue(o);
            found = true;
        }
        else {
            temp.enqueue(o);
        }
    }
    while (!temp.isEmpty()) {
        pendingOVC->enqueue(temp.dequeue());
    }
    return found;
}

bool Restaurant::RemoveFromCookingOVC(int id) {
    return cookingOrders->CancelOrder(id);
}

bool Restaurant::RemoveFromReadyOVC(int id) {
    Queue<Order*> temp;
    bool found = false;
    while (!readyOrders->isEmpty()) {
        Order* o = readyOrders->dequeue();
        if (o->id == id) {
            cancelledOrders->enqueue(o);
            found = true;
        }
        else {
            temp.enqueue(o);
        }
    }
    while (!temp.isEmpty()) {
        readyOrders->enqueue(temp.dequeue());
    }
    return found;
}

void Restaurant::ReleaseChefFromOrder(int id) {
    // Placeholder – will be implemented by Shahd
}

// ==================== EXISTING TABLE FUNCTIONS (unchanged) ====================
void Restaurant::AssignTable(int timestep) {
    if (readyOrders->isEmpty()) return;
    if (occupiedTables->isEmpty() && freeTables->isEmpty()) return;

    Order* nextOrder = readyOrders->peekFront();
    int orderSize = nextOrder->getSize();
    Table* foundTable = nullptr;
    bool isNewTable = false;

    // Search occupied sharable tables
    Queue<Table*> tempOccupied;
    while (!occupiedTables->isEmpty()) {
        Table* t = occupiedTables->dequeue();
        if (t->isSharable() && (t->getCapacity() - t->getCurrentload() >= orderSize) && !foundTable) {
            foundTable = t;
        }
        tempOccupied.enqueue(t);
    }
    while (!tempOccupied.isEmpty()) occupiedTables->enqueue(tempOccupied.dequeue());

    // Search free tables
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

    if (foundTable) {
        readyOrders->dequeue();
        nextOrder->finishTime = timestep + nextOrder->duration;
        inServiceOrders->enqueue(nextOrder, (100000 - nextOrder->finishTime));
        foundTable->assignorder(nextOrder);
        if (isNewTable) occupiedTables->enqueue(foundTable);
    }
}

void Restaurant::FreeFinishedTables(int timestep) {
    if (inServiceOrders->isEmpty()) return;

    Order* pOrd;
    int pri;

    while (inServiceOrders->peek(pOrd, pri)) {
        if (pOrd->getFinishTime() <= timestep) {
            inServiceOrders->dequeue(pOrd, pri);
            int tID = pOrd->getTableID();

            Queue<Table*> tempOccupied;
            Table* targetTable = nullptr;

            while (!occupiedTables->isEmpty()) {
                Table* t = occupiedTables->dequeue();
                if (t->getTabelID() == tID) {
                    targetTable = t;
                }
                else {
                    tempOccupied.enqueue(t);
                }
            }

            if (targetTable) {
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