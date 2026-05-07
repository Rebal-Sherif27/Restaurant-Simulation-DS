#pragma once
#ifndef SCOOTER_H
#define SCOOTER_H

class Scooter
{
private:
	int ID;               
	int	Speed;            
	int Main_Dur;          
	int Main_Ords;       
	int	OrderServed;     
	int maintEndTime;
public:
	Scooter();
	Scooter(int id, int speeed, int mainDur, int mainOrds);

	int getID() const;
	int getSpeed() const;
	int getMainDur() const;
	int getMainOrds() const;
	int getOrderServed() const;

	void setID(int id);
	void setSpeed(int speed);
	void setMainDur(int mainDur);
	void setMainOrds(int mainOrds);

	void increaseOrderServed(); 
	void resetOrderServed();
	bool needsMaintenance() const; 

	void print() const;

	void setMaintEndTime(int time);
	int getMaintEndTime() const;

};
#endif

