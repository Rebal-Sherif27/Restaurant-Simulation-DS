#include "Table.h"
#include "order.h" 

void Table::assignOrder(Order* newOrder) {
	currentOrder = newOrder;
	currentLoad = newOrder->getNumPeople();
}

void Table::freeTable() {
    currentOrder = nullptr;
    currentLoad = 0;
    // You may need to store the "original" sharability in a separate 
    // variable like 'originalSharable' if you want to reset it properly here.
}

void Table::setSharable(bool status) {
	isSharable = status;
}
