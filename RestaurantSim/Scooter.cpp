#include "Scooter.h"
#include <iostream>
//consrtuctors:
Scooter::Scooter() : ID(0), Speed(0), Main_Dur(0), Main_Ords(0), OrderServed(0) {}

Scooter::Scooter(int id, int speed, int mainDur, int mainOrds)
	: ID(id), Speed(speed), Main_Dur(mainDur), Main_Ords(mainOrds), OrderServed(0) {}


//Getters:
int Scooter::getID() const { return ID; }
int Scooter::getSpeed() const { return Speed; }
int Scooter::getMainDur() const { return Main_Dur; }
int Scooter::getMainOrds() const { return Main_Ords; }
int Scooter::getOrderServed() const { return OrderServed; }
//---------------------------------------------------------------------
//Setters:
void Scooter::setID(int id) { ID = id; }
void Scooter::setSpeed(int speed) { Speed = speed; }
void Scooter::setMainDur(int mainDur) { Main_Dur = mainDur; }
void Scooter::setMainOrds(int mainOrds) { Main_Ords = mainOrds; }
//---------------------------------------------------------------------
void Scooter::increaseOrderServed() { OrderServed++; }
void Scooter::resetOrderServed() { OrderServed = 0; }
bool Scooter::needsMaintenance() const { return OrderServed >= Main_Ords; }
//----------------------------------------------------------------------
void Scooter::print() const
{
	std::cout << "Scooter ID: " << ID << ", Speed: " << Speed
		<< " m/timestep, Maintenance Duration: " << Main_Dur
		<< " timesteps, Orders before Maintenance: " << Main_Ords
		<< ", Orders Served: " << OrderServed << std::endl;
}


