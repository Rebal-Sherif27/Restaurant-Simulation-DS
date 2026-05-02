#include "Order.h"

Order::Order(int id, OrderType t, int sz, int prc, int reqTime) {
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;
    this->requestTime = reqTime;

    // Initialize defaults from the header
    this->seats = 0;
    this->duration = 0;
    this->canShare = false;
    this->distance = 0;

    // Initialize tracking data
    this->finishTime = 0;
    this->resourceID = -1;
    this->resourceType = "";
    this->tableID = -1;
}

Order::~Order() {
    // Destructor logic (if any)
}

int Order::getNumPeople() const {
    return size;
}