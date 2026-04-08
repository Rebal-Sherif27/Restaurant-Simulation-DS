#pragma once
#include <string>
using namespace std;

enum OrderType {
    ODG,  // dine-in grilled
    ODN,  // dine-in normal
    OT,   // takeaway
    OVG,  // delivery grilled
    OVC,  // delivery cold
    OVN   // delivery normal
};

class Order {
public:
    int getNumPeople() const {
        // For dine-in orders return the seats count; for others default to 1
        return (type == ODG || type == ODN) ? seats : 1;
    }

    int id;
    OrderType type;
    int size;
    int price;
    int requestTime;

    // For dine-in only
    int seats;
    int duration;
    bool canShare;

    // For delivery only
    int distance;

    Order(int id, OrderType t, int size, int price, int reqTime);
    ~Order();
};

