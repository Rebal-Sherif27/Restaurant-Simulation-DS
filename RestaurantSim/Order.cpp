#include "Order.h"

Order::Order(int id, OrderType t, int sz, int prc, int reqTime) {
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;
    this->requestTime = reqTime;
    seats = 0;
    duration = 0;
    canShare = false;
    distance = 0;
}

Order::~Order() {}

int Order::getNumPeople() const {
    // Returns the party size
    return size;
}