#pragma once
#include <string>
using namespace std;

enum OrderType {
    ODG, ODN, OT, OVG, OVC, OVN
};

class Order {
    int tableID = -1; // Keep this private
public:
    int id;
    OrderType type;
    int size;
    int price;
    int requestTime;
    int seats;
    int duration;
    bool canShare;
    int distance;

    // Tracking Data
    int finishTime;
    int resourceID;
    string resourceType;

    Order(int id, OrderType t, int size, int price, int reqTime);
    ~Order();

    // Getters
    int getNumPeople() const;
    int getTableID() const { return tableID; }
    int getFinishTime() const { return finishTime; }
    int getSize() const { return size; }
};