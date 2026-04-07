#pragma once

class Order; // <-- This is the Forward Declaration. It tells the compiler "Order exists, trust me."

class Table {
private:
	int tableID;
	int capacity;
	int currentLoad;
	bool isSharable;
	Order* currentOrder;

public:
	Table(int id, int capacity, bool sharable);
	int getTableID() const;
	int getCapacity() const;
	int getCurrentLoad() const;
	bool getIsSharable() const;
	void setCurrentLoad(int load);

	// Core Functions
	void assignOrder(Order* newOrder);
	void freeTable();
};
////jody


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


