#pragma once
#include <string>
using namespace std;


enum OrderType 
{
    ODG, ODN, OT, OVG, OVC, OVN
};

class Chef;
class Scooter;

class Order 
{
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
    Chef* assignedChef;
    Scooter* assignedScooter;

    int finishTime;
    int resourceID;
    string resourceType;

    int assignTime;
    int readyTime;
    int serviceStartTime;

    Order(int id, OrderType t, int size, int price, int reqTime);

    Order(int reqTime, int id, OrderType t, int sz, int pr, int st, int dur, bool share, int dist);

    ~Order();

    int getNumPeople() const;
    int getTableID() const { return tableID; }
    int getFinishTime() const { return finishTime; }
    int getSize() const { return size; }
};