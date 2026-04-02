#pragma once
#include <iostream>

enum ChefType
{
    CS,
    CN
};

class Chef
{
private:
    int ID;
    ChefType Type;
    int Speed;

public:
    Chef();
    Chef(int id, ChefType type, int speed);

    int GetID() const;
    ChefType GetType() const;
    int GetSpeed() const;

    void SetID(int id);
    void SetType(ChefType type);
    void SetSpeed(int speed);

    void Print() const;
};

std::ostream& operator<<(std::ostream& out, const Chef& chef);