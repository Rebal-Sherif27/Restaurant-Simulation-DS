#include "order.h"

// Constructor implementation
order::order(int id, int people) {
    orderID = id;
    numPeople = people;
}

// Getters implementation
int order::getOrderID() const {
    return orderID;
}

int order::getNumPeople() const {
    return numPeople;
}