#include "Order.h"
Order::Order(int id, OrderType t, int size, int price, int reqTime) {
    this->id = id;
    this->type = t;
    this->size = size;
    this->price = price;
    this->requestTime = reqTime;
    seats = 0;
    duration = 0;
    canShare = false;
    distance = 0;
}

Order::~Order() {}