#pragma once
#include <string>
using namespace std;

enum OrderType {
    ODG, ODN, OT, OVG, OVC, OVN
};

class Order {
public:
    int getNumPeople() const;

    int id;
    OrderType type;
    int size;
    int price;
    int requestTime;
    int seats;
    int duration;
    bool canShare;
    int distance;

    // ADDED FOR TRACKING
    int finishTime;
    int resourceID;
    string resourceType;

    Order(int id, OrderType t, int size, int price, int reqTime);
    ~Order();
};