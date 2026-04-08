
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

