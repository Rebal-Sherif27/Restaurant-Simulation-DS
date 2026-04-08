#include "Table.h"
#include "Order.h"

using namespace std;

Table::Table(int id, int cap, bool sharable) {
    tabelID = id;
    capacity = cap;
    issharabel = sharable;
    currentload = 0;
    currentorder = nullptr;
}

void Table::assignorder(Order* neworder) {
    currentorder = neworder;
    currentload = neworder->getNumPeople();
}

void Table::freeTable() {
    currentorder = nullptr;
    currentload = 0;
    // You may need to store the "original" sharability in a separate 
    // variable like 'originalSharable' if you want to reset it properly here.
}

void Table::setSharable(bool status) {
    issharabel = status;
}