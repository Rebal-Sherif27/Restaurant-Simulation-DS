#pragma once
class Table
{
	int tabelID;
	int capcity;
	int currentload;
	bool issharabel;
	Order* currentOrder;
public:
	Table(int id, int capcity, bool sharable);
	int getTabelID() const;
	int getCapcity() const;
	int getCurrentload() const;
	bool isSharable() const;
	void setCurrentload(int load);
	void setSharable(bool status);
	// Core Functions
	void assignOrder(Order* newOrder);
	void freeTable();

};

