#pragma once
#include <string>

using namespace std;

enum OrderType {
    ODG, ODN, OT, OVG, OVC, OVN
};

class Order {
public:
    // Declaration ONLY - ends with a semicolon
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

    Order(int id, OrderType t, int size, int price, int reqTime);
    ~Order();
};