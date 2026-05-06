#pragma once
#ifndef SCOOTER_H
#define SCOOTER_H

class Scooter
{
private:
	int ID;               //ID of the scooter
	int	Speed;            //speed of the scooter in meters/timestep
	int Main_Dur;         // Maintenanace duration 
	int Main_Ords;        //The number of orders before maintenanace is needed
	int	OrderServed;  //How many orders it has delivered so far
	int maintEndTime;
public:
	//Constructors:
	Scooter();
	Scooter(int id, int speeed, int mainDur, int mainOrds);
	//Getters:
	int getID() const;
	int getSpeed() const;
	int getMainDur() const;
	int getMainOrds() const;
	int getOrderServed() const;
	//Setters:
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

