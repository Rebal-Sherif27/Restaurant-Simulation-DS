#include <iostream>
#include "LinkedQueue.h"
#include "Order.h"
#include "table.h"
#include "priQueue.h"
using namespace std;

using namespace std;

int testMain() {
    
    LinkedQueue<Order*> ReadyOT;
    LinkedQueue<Table*> FreeTables;
    priQueue<Table*> BusySharable;
    LinkedQueue<Table*> BusyNoShare;

    
    Table* t1 = new Table(1, 4, true);  
    Table* t2 = new Table(2, 2, false); 
    Table* t3 = new Table(3, 6, true);  

    FreeTables.enqueue(t1);
    FreeTables.enqueue(t2);
    FreeTables.enqueue(t3);

    cout << "Simulation Initialized." << endl;
    cout << "Available Tables: " << FreeTables.getCount() << endl;


    return 0;
}