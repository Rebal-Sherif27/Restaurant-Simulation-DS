#include "Restaurant.h"
#include <cmath>

using namespace std;

void Restaurant::AssignPendingToChef(int currentTime)
{
    while (!pendingODG->isEmpty() && !freeCS->isEmpty())
    {
        Order* pOrd = pendingODG->dequeue();
        Chef* pChef = nullptr;

        freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;

        int cookTime = ceil((double)pOrd->size / pChef->GetSpeed());
        pOrd->readyTime = currentTime + cookTime;

        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    while (!pendingODN->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
    {
        Order* pOrd = pendingODN->dequeue();
        Chef* pChef = nullptr;

        if (!freeCN->isEmpty())
            freeCN->dequeue(pChef);
        else
            freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;

        int cookTime = ceil((double)pOrd->size / pChef->GetSpeed());
        pOrd->readyTime = currentTime + cookTime;

        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    while (!pendingOT->isEmpty() && !freeCN->isEmpty())
    {
        Order* pOrd = pendingOT->dequeue();
        Chef* pChef = nullptr;

        freeCN->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;

        int cookTime = ceil((double)pOrd->size / pChef->GetSpeed());
        pOrd->readyTime = currentTime + cookTime;

        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    while (!pendingOVG->isEmpty() && !freeCS->isEmpty())
    {
        Order* pOrd = pendingOVG->dequeue();
        Chef* pChef = nullptr;

        freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;

        int cookTime = ceil((double)pOrd->size / pChef->GetSpeed());
        pOrd->readyTime = currentTime + cookTime;

        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    while (!pendingOVC->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
    {
        Order* pOrd = pendingOVC->dequeue();
        Chef* pChef = nullptr;

        if (!freeCN->isEmpty())
            freeCN->dequeue(pChef);
        else
            freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;

        int cookTime = ceil((double)pOrd->size / pChef->GetSpeed());
        pOrd->readyTime = currentTime + cookTime;

        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    while (!pendingOVN->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
    {
        Order* pOrd = pendingOVN->dequeue();
        Chef* pChef = nullptr;

        if (!freeCN->isEmpty())
            freeCN->dequeue(pChef);
        else
            freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;

        int cookTime = ceil((double)pOrd->size / pChef->GetSpeed());
        pOrd->readyTime = currentTime + cookTime;

        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }
}

void Restaurant::MoveCookingToReady(int currentTime)
{
    Order* pOrd = nullptr;
    int priority;

    while (cookingOrders->peek(pOrd, priority))
    {
        if (pOrd == nullptr)
            break;

        if (pOrd->readyTime > currentTime)
            break;

        cookingOrders->dequeue(pOrd, priority);

        if (pOrd->assignedChef != nullptr)
        {
            if (pOrd->assignedChef->GetType() == CS)
            {
                freeCS->enqueue(pOrd->assignedChef);
            }
            else
            {
                freeCN->enqueue(pOrd->assignedChef);
            }

            pOrd->assignedChef = nullptr;
        }

        if (pOrd->type == ODG || pOrd->type == ODN)
        {
            readyDineIn->enqueue(pOrd);
        }
        else if (pOrd->type == OT)
        {
            readyTakeaway->enqueue(pOrd);
        }
        else
        {
            readyDelivery->enqueue(pOrd);
        }
    }
}

void Restaurant::FinalizeTakeawayOrders(int currentTime)
{
    while (!readyTakeaway->isEmpty())
    {
        Order* pOrd = readyTakeaway->peekFront();

        if (currentTime < pOrd->readyTime + 1)
        {
            break;
        }

        pOrd = readyTakeaway->dequeue();

        pOrd->finishTime = currentTime;

        finishedOrders->push(pOrd);
    }
}