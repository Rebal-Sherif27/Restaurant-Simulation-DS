#pragma once
#include <string>
using namespace std;

enum OrderType {
    ODG, ODN, OT, OVG, OVC, OVN
};

class Order {
    int tableID = -1;
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

    // New fields for your features
    int assignTime;
    int readyTime;
    int serviceStartTime;

    // Old constructor (kept for compatibility)
    Order(int id, OrderType t, int size, int price, int reqTime);

    // New constructor (for your RequestAction)
    Order(int reqTime, int id, OrderType t, int sz, int pr, int st, int dur, bool share, int dist);

    ~Order();

    int getNumPeople() const;
    int getTableID() const { return tableID; }
    int getFinishTime() const { return finishTime; }
    int getSize() const { return size; }

};