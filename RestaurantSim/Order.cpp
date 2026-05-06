#include "Order.h"
using namespace std;

Order::Order(int id, OrderType t, int sz, int prc, int reqTime) {
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;
    this->requestTime = reqTime;
    assignedChef = nullptr;

    this->seats = 0;
    this->duration = 0;
    this->canShare = false;
    this->distance = 0;

    this->finishTime = 0;
    this->resourceID = -1;
    this->resourceType = "";
    this->tableID = -1;

    // new fields
    this->assignTime = -1;
    this->readyTime = -1;
    this->serviceStartTime = -1;
}

Order::Order(int reqTime, int id, OrderType t, int sz, int pr, int st, int dur, bool share, int dist)
{
    this->requestTime = reqTime;
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = pr;

    this->seats = st;
    this->duration = dur;
    this->canShare = share;
    this->distance = dist;

    this->finishTime = 0;
    this->resourceID = -1;
    this->resourceType = "";
    this->tableID = -1;

    this->assignTime = -1;
    this->readyTime = -1;
    this->serviceStartTime = -1;

    this->assignedChef = nullptr;
}

Order::~Order() {}

int Order::getNumPeople() const {
    return size;
}