#include <iostream>
#include "LinkedQueue.h"
#include "Order.h"
#include "table.h"
#include "priQueue.h"
// #include "Fit_Tables.h" // Keep this if it contains your assignment logic

using namespace std;

int testMain() {
    // 1. Instantiate the Containers
    // IMPORTANT: Make sure 'order' and 'Table' match your .h file capitalization exactly.
    LinkedQueue<Order*> ReadyOT;
    LinkedQueue<Table*> FreeTables;
    priQueue<Table*> BusySharable;
    LinkedQueue<Table*> BusyNoShare;

    // 2. Initialize the Tables (Simulation Setup)
    // You cannot have a simulation with 0 tables.
    // In the real project, this will be done via a file-loader loop.
    Table* t1 = new Table(1, 4, true);  // ID 1, Cap 4, Sharable
    Table* t2 = new Table(2, 2, false); // ID 2, Cap 2, Private
    Table* t3 = new Table(3, 6, true);  // ID 3, Cap 6, Sharable

    FreeTables.enqueue(t1);
    FreeTables.enqueue(t2);
    FreeTables.enqueue(t3);

    // 3. Test Output
    cout << "Simulation Initialized." << endl;
    cout << "Available Tables: " << FreeTables.getCount() << endl;

    // Your logic for moving tables between lists goes here (likely inside a loop)

    return 0;
}