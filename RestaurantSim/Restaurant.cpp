#include "Restaurant.h"
#include <cstdlib>
#include <ctime>

Restaurant::Restaurant() {
    currentTime = 0;
    srand(time(NULL));
}

Restaurant::~Restaurant() {
    // Cleanup orders from all queues
    while (!pendingODG.isEmpty()) delete pendingODG.dequeue();
    while (!pendingODN.isEmpty()) delete pendingODN.dequeue();
    while (!pendingOT.isEmpty()) delete pendingOT.dequeue();
    while (!pendingOVG.isEmpty()) delete pendingOVG.dequeue();
    while (!pendingOVC.isEmpty()) delete pendingOVC.dequeue();
    while (!pendingOVN.isEmpty()) delete pendingOVN.dequeue();
    while (!cookingOVC.isEmpty()) delete cookingOVC.dequeue();
    while (!readyOVC.isEmpty()) delete readyOVC.dequeue();
}

void Restaurant::addPendingODG(Order* o) { pendingODG.enqueue(o); }
void Restaurant::addPendingODN(Order* o) { pendingODN.enqueue(o); }
void Restaurant::addPendingOT(Order* o) { pendingOT.enqueue(o); }
void Restaurant::addPendingOVG(Order* o) { pendingOVG.enqueue(o); }
void Restaurant::addPendingOVC(Order* o) { pendingOVC.enqueue(o); }
void Restaurant::addPendingOVN(Order* o) { pendingOVN.enqueue(o); }

bool Restaurant::RemoveFromPendingOVC(int orderID) {
    Queue<Order*> temp;
    bool found = false;

    while (!pendingOVC.isEmpty()) {
        Order* o = pendingOVC.dequeue();
        if (o->id == orderID) {
            delete o;
            found = true;
            cancelledOrders.enqueue(orderID);
        }
        else {
            temp.enqueue(o);
        }
    }

    while (!temp.isEmpty()) {
        pendingOVC.enqueue(temp.dequeue());
    }

    return found;
}

bool Restaurant::RemoveFromCookingOVC(int orderID) {
    Queue<Order*> temp;
    bool found = false;

    while (!cookingOVC.isEmpty()) {
        Order* o = cookingOVC.dequeue();
        if (o->id == orderID) {
            delete o;
            found = true;
            cancelledOrders.enqueue(orderID);
        }
        else {
            temp.enqueue(o);
        }
    }

    while (!temp.isEmpty()) {
        cookingOVC.enqueue(temp.dequeue());
    }

    return found;
}

bool Restaurant::RemoveFromReadyOVC(int orderID) {
    Queue<Order*> temp;
    bool found = false;

    while (!readyOVC.isEmpty()) {
        Order* o = readyOVC.dequeue();
        if (o->id == orderID) {
            delete o;
            found = true;
            cancelledOrders.enqueue(orderID);
        }
        else {
            temp.enqueue(o);
        }
    }

    while (!temp.isEmpty()) {
        readyOVC.enqueue(temp.dequeue());
    }

    return found;
}

void Restaurant::ReleaseChefFromOrder(int orderID) {
    // For Phase 1.2, just print
    cout << "Chef released from order #" << orderID << endl;
}

void Restaurant::GenerateRandomPendingOrders(int count) {
    for (int i = 0; i < count; i++) {
        int typeIdx = rand() % 6;
        int id = i + 500;
        int size = rand() % 20 + 1;
        int price = rand() % 500 + 50;

        OrderType t;
        switch (typeIdx) {
        case 0: t = ODG; break;
        case 1: t = ODN; break;
        case 2: t = OT; break;
        case 3: t = OVG; break;
        case 4: t = OVC; break;
        default: t = OVN; break;
        }

        Order* o = new Order(id, t, size, price, 0);

        if (t == ODG || t == ODN) {
            o->seats = rand() % 8 + 1;
            o->duration = rand() % 30 + 10;
            o->canShare = rand() % 2;
        }
        if (t == OVG || t == OVC || t == OVN) {
            o->distance = rand() % 1000 + 100;
        }

        switch (t) {
        case ODG: pendingODG.enqueue(o); break;
        case ODN: pendingODN.enqueue(o); break;
        case OT: pendingOT.enqueue(o); break;
        case OVG: pendingOVG.enqueue(o); break;
        case OVC: pendingOVC.enqueue(o); break;
        case OVN: pendingOVN.enqueue(o); break;
        }
    }
}

void Restaurant::PrintAllLists() {
    cout << "\n--- PENDING LISTS ---\n";
    cout << "ODG count: " << pendingODG.getCount() << endl;
    cout << "ODN count: " << pendingODN.getCount() << endl;
    cout << "OT count: " << pendingOT.getCount() << endl;
    cout << "OVG count: " << pendingOVG.getCount() << endl;
    cout << "OVC count: " << pendingOVC.getCount() << endl;
    cout << "OVN count: " << pendingOVN.getCount() << endl;
    cout << "\n--- COOKING LISTS ---\n";
    cout << "Cooking OVC count: " << cookingOVC.getCount() << endl;
    cout << "\n--- READY LISTS ---\n";
    cout << "Ready OVC count: " << readyOVC.getCount() << endl;
    cout << "\n--- CANCELLED ---\n";
    cout << "Cancelled orders count: " << cancelledOrders.getCount() << endl;
}
void Restaurant::PrintAllLists() {
    cout << "\n=== PENDING LISTS ===\n";

    cout << "ODG: ";
    pendingODG.printIDs();

    cout << "ODN: ";
    pendingODN.printIDs();

    cout << "OT: ";
    pendingOT.printIDs();

    cout << "OVG: ";
    pendingOVG.printIDs();

    cout << "OVC: ";
    pendingOVC.printIDs();

    cout << "OVN: ";
    pendingOVN.printIDs();

    cout << "\nRDY_OVC: ";
    readyOVC.printIDs();

    cout << "\nCANCELLED ORDERS: ";
    cancelledOrders.print();
}
