#include "Chef.h"

Chef::Chef()
{
    ID = 0;
    Type = CN;
    Speed = 0;
}

Chef::Chef(int id, ChefType type, int speed)
{
    ID = id;
    Type = type;
    Speed = speed;
}

int Chef::GetID() const
{return ID;}

ChefType Chef::GetType() const
{return Type;}

int Chef::GetSpeed() const
{ return Speed;}

void Chef::SetID(int id)
{ ID = id;}

void Chef::SetType(ChefType type)
{ Type = type;}

void Chef::SetSpeed(int speed)
{ Speed = speed;}

void Chef::Print() const
{
    std::cout << "Chef[ID=" << ID << ", Type=" << (Type == CS ? "CS" : "CN")
              << ", Speed=" << Speed << "]";
}

std::ostream& operator<<(std::ostream& out, const Chef& chef)
{
    out << "Chef[ID=" << chef.GetID()
        << ", Type=" << (chef.GetType() == CS ? "CS" : "CN")
        << ", Speed=" << chef.GetSpeed() << "]";
    return out;
}
