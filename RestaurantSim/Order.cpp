#include "Order.h"

// ADD THIS BELOW YOUR EXISTING CONSTRUCTOR IN ORDER.CPP
Order::Order(int rTime, int id, OrderType t, int sz, int prc, int st, int dur, bool share, int dist) {
    this->requestTime = rTime;
    this->id = id;
    this->type = t;
    this->size = sz;
    this->price = prc;
<<<<<<< HEAD
=======
    this->requestTime = reqTime;
    assignedChef = nullptr;
>>>>>>> 61d3aee0d4f32a99e3d7f92539c3302bf8f288e4

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
<<<<<<< HEAD
=======

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

>>>>>>> 61d3aee0d4f32a99e3d7f92539c3302bf8f288e4
Order::~Order() {}

int Order::getNumPeople() const {
    return size;
}