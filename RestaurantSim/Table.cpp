#include "Table.h"
#include "order.h" 

void Table::assignorder(order* neworder) {
    currentorder = neworder;
    currentload = neworder->getNumPeople();
};

void Table::freeTable() {
    currentorder = nullptr;
    currentload = 0;
    // You may need to store the "original" sharability in a separate 
    // variable like 'originalSharable' if you want to reset it properly here.
};

void Table::setSharable(bool status) {
    issharabel = status;
}
