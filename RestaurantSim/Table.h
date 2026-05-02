#pragma once
#include "Order.h"

class Table
{
	int tabelID;
	int capacity;
	int currentload;
	bool issharable;
	Order* currentorder;
	bool isReserved;    
public:
	Table(int id, int capacity, bool sharable);
	int getTabelID() const;
	int getCapacity() const;
	int getCurrentload() const;
	bool isSharable() const;
	void setCurrentload(int load);
	void setSharable(bool status);
	bool checkReserved() const;    
	void setReserved(bool status);  


	// Core Functions
	void assignorder(Order* neworder);
	void freeTable();

};