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

