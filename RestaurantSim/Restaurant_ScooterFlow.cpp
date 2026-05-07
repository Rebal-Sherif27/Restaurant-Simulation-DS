#include "Restaurant.h"
#include <cmath>

using namespace std;

void Restaurant::AssignScooter(int currentTime)
{
    while (!readyDelivery->isEmpty() && !freeScooters->isEmpty())
    {
        Order* pOrd = readyDelivery->dequeue();
        Scooter* pScooter = nullptr;
        int priority;

        if (!freeScooters->dequeue(pScooter, priority))
        {
            readyDelivery->enqueue(pOrd);
            break;
        }

        pOrd->assignedScooter = pScooter;
        pOrd->serviceStartTime = currentTime;

        int deliveryTime = 0;

        if (pScooter->getSpeed() > 0)
        {
            deliveryTime = (int)ceil((double)pOrd->distance / pScooter->getSpeed());
        }

        pOrd->finishTime = currentTime + deliveryTime;

        deliveryOrders->enqueue(pOrd, 100000 - pOrd->finishTime);
    }
}

void Restaurant::CheckFinishedDeliveryOrders(int currentTime)
{
    Order* pOrd = nullptr;
    int priority;

    while (deliveryOrders->peek(pOrd, priority))
    {
        if (pOrd == nullptr)
        {
            break;
        }

        if (pOrd->finishTime > currentTime)
        {
            break;
        }

        deliveryOrders->dequeue(pOrd, priority);

        Scooter* pScooter = pOrd->assignedScooter;

        if (pScooter != nullptr)
        {
            pScooter->increaseOrderServed();

            int returnTime = currentTime;

            if (pScooter->getSpeed() > 0)
            {
                returnTime = currentTime + (int)ceil((double)pOrd->distance / pScooter->getSpeed());
            }

            pScooter->setMaintEndTime(returnTime);

            backScooters->enqueue(pScooter, 100000 - returnTime);

            pOrd->assignedScooter = nullptr;
        }

        finishedOrders->push(pOrd);
    }
}

void Restaurant::CheckBackScooters(int currentTime)
{
    Scooter* pScooter = nullptr;
    int priority;

    while (backScooters->peek(pScooter, priority))
    {
        if (pScooter == nullptr)
        {
            break;
        }

        if (pScooter->getMaintEndTime() > currentTime)
        {
            break;
        }

        backScooters->dequeue(pScooter, priority);

        if (pScooter->needsMaintenance())
        {
            pScooter->setMaintEndTime(currentTime + pScooter->getMainDur());
            maintScooters->enqueue(pScooter);
        }
        else
        {
            freeScooters->enqueue(pScooter, pScooter->getSpeed());
        }
    }
}

void Restaurant::CheckScooterMaintenance(int currentTime)
{
    MaintScooters temp;

    while (!maintScooters->isEmpty())
    {
        Scooter* pScooter = nullptr;
        maintScooters->dequeue(pScooter);

        if (pScooter != nullptr && pScooter->getMaintEndTime() <= currentTime)
        {
            pScooter->resetOrderServed();
            freeScooters->enqueue(pScooter, pScooter->getSpeed());
        }
        else if (pScooter != nullptr)
        {
            temp.enqueue(pScooter);
        }
    }

    while (!temp.isEmpty())
    {
        Scooter* pScooter = nullptr;
        temp.dequeue(pScooter);
        maintScooters->enqueue(pScooter);
    }
}