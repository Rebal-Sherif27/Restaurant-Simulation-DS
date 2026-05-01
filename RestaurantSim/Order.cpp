#include "Order.h"

Order::Order(int id, OrderType t, int sz, int prc, int reqTime) {
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;
    this->requestTime = reqTime;

    // Initialize defaults
    seats = 0;
    duration = 0;
    canShare = false;
    distance = 0;

    // INITIALIZE TRACKING DATA
    finishTime = 0;
    resourceID = -1;
    resourceType = "";
}

Order::~Order() {}

int Order::getNumPeople() const {
    return size;
}