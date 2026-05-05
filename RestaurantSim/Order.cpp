#include "Order.h"

Order::Order(int id, OrderType t, int sz, int prc, int reqTime) {
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;
    this->requestTime = reqTime;

    this->seats = 0;
    this->duration = 0;
    this->canShare = false;
    this->distance = 0;

    this->finishTime = 0;
    this->resourceID = -1;
    this->resourceType = "";
    this->tableID = -1;

    // Initialize new fields
    this->assignTime = -1;
    this->readyTime = -1;
    this->serviceStartTime = -1;
}

Order::~Order() {}

int Order::getNumPeople() const {
    return size;
}