#include "Order.h"

// ADD THIS BELOW YOUR EXISTING CONSTRUCTOR IN ORDER.CPP
Order::Order(int rTime, int id, OrderType t, int sz, int prc, int st, int dur, bool share, int dist) {
    this->requestTime = rTime;
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;

    // Parameters from the file
    this->seats = st;
    this->duration = dur;
    this->canShare = share;
    this->distance = dist;

    // Default tracking data
    this->finishTime = 0;
    this->resourceID = -1;
    this->resourceType = "";
    this->tableID = -1;

    this->assignTime = -1;
    this->readyTime = -1;
    this->serviceStartTime = -1;
}
Order::~Order() {}

int Order::getNumPeople() const {
    return size;
}