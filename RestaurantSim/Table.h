#pragma once

class Table
{
	int tabelID;
	int capacity;
	int currentload;
	bool issharabel;
	order* currentorder;
public:
	Table(int id, int capacity, bool sharable);
	int getTabelID() const;
	int getCapacity() const;
	int getCurrentload() const;
	bool isSharable() const;
	void setCurrentload(int load);
	void setSharable(bool status);
	// Core Functions
	void assignorder(order* neworder);
	void freeTable();

};