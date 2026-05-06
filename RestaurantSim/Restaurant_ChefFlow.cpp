#include "Restaurant.h"
#include<cmath>

using namespace std;

void Restaurant::AssignPendingToChef(int currentTime)
{
    // 1. ODG (Only CS Chefs)
    while (!pendingODG->isEmpty() && !freeCS->isEmpty())
    {
        Order* pOrd = pendingODG->dequeue(); // 0 arguments for Order Queue
        Chef* pChef;
        freeCS->dequeue(pChef);              // 1 argument for Chef Queue

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;
        int cookTime = (pOrd->size + pChef->GetSpeed() - 1) / pChef->GetSpeed();
        pOrd->readyTime = currentTime + cookTime;

        // Priority Queue needs 2 arguments: the order and the priority value
        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

<<<<<<< HEAD
    // 2. ODN (CN then CS)
    while (!pendingODN->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
    {
        Order* pOrd = pendingODN->dequeue();
        Chef* pChef = nullptr;

        if (!freeCN->isEmpty()) freeCN->dequeue(pChef);
        else freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;
        int cookTime = (pOrd->size + pChef->GetSpeed() - 1) / pChef->GetSpeed();
        pOrd->readyTime = currentTime + cookTime;
        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    // 3. OT (Only CN)
    while (!pendingOT->isEmpty() && !freeCN->isEmpty())
    {
        Order* pOrd = pendingOT->dequeue();
        Chef* pChef;
        freeCN->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;
        int cookTime = (pOrd->size + pChef->GetSpeed() - 1) / pChef->GetSpeed();
        pOrd->readyTime = currentTime + cookTime;
        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    // 4. OVG (Only CS)
    while (!pendingOVG->isEmpty() && !freeCS->isEmpty())
    {
        Order* pOrd = pendingOVG->dequeue();
        Chef* pChef;
        freeCS->dequeue(pChef);

        pOrd->assignedChef = pChef;
        pOrd->assignTime = currentTime;
        int cookTime = (pOrd->size + pChef->GetSpeed() - 1) / pChef->GetSpeed();
        pOrd->readyTime = currentTime + cookTime;
        cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
    }

    // 5. OVC & 6. OVN (CN then CS)
    Queue<Order*>* extraQueues[] = { pendingOVC, pendingOVN };
    for (int i = 0; i < 2; i++) {
        while (!extraQueues[i]->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty())) {
            Order* pOrd = extraQueues[i]->dequeue();
            Chef* pChef = nullptr;
            if (!freeCN->isEmpty()) freeCN->dequeue(pChef);
            else freeCS->dequeue(pChef);

            pOrd->assignedChef = pChef;
            pOrd->assignTime = currentTime;
            int cookTime = (pOrd->size + pChef->GetSpeed() - 1) / pChef->GetSpeed();
            pOrd->readyTime = currentTime + cookTime;
            cookingOrders->enqueue(pOrd, 100000 - pOrd->readyTime);
=======
            int cookTime = ceil((double)order->size / chef->GetSpeed());
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingODN->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
        {
            Order* order = pendingODN->dequeue();
            Chef* chef;

            if (!freeCN->isEmpty())
                chef = freeCN->dequeue();
            else
                chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = ceil((double)order->size / chef->GetSpeed());
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingOT->isEmpty() && !freeCN->isEmpty())
        {
            Order* order = pendingOT->dequeue();
            Chef* chef = freeCN->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = ceil((double)order->size / chef->GetSpeed());
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingOVG->isEmpty() && !freeCS->isEmpty())
        {
            Order* order = pendingOVG->dequeue();
            Chef* chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = ceil((double)order->size / chef->GetSpeed());
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingOVC->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
        {
            Order* order = pendingOVC->dequeue();
            Chef* chef;

            if (!freeCN->isEmpty())
                chef = freeCN->dequeue();
            else
                chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = ceil((double)order->size / chef->GetSpeed());
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingOVN->isEmpty() && (!freeCN->isEmpty() || !freeCS->isEmpty()))
        {
            Order* order = pendingOVN->dequeue();
            Chef* chef;

            if (!freeCN->isEmpty())
                chef = freeCN->dequeue();
            else
                chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = ceil((double)order->size / chef->GetSpeed());
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
>>>>>>> shahd-chef-flow-phase2
        }
    }
}

<<<<<<< HEAD
void Restaurant::MoveCookingToReady(int currentTime) {}
void Restaurant::FinalizeTakeawayOrders(int currentTime) {}
=======

void Restaurant::MoveCookingToReady(int currentTime)
{
   
        Order* order = nullptr;
        int priority;

        while (cookingOrders->peek(order, priority))
        {
            if (order == nullptr)
                break;

            if (order->readyTime > currentTime)
                break;

            cookingOrders->dequeue(order, priority);

            if (order->assignedChef != nullptr)
            {
                if (order->assignedChef->GetType() == CS)
                {
                    freeCS->enqueue(order->assignedChef);
                }
                else
                {
                    freeCN->enqueue(order->assignedChef);
                }

                order->assignedChef = nullptr;
            }

            if (order->type == ODG || order->type == ODN)
            {
                readyDineIn->enqueue(order);
            }
            else if (order->type == OT)
            {
                readyTakeaway->enqueue(order);
            }
            else
            {
                readyDelivery->enqueue(order);
            }
        }
    
}

void Restaurant::FinalizeTakeawayOrders(int currentTime)
{
    
        while (!readyTakeaway->isEmpty())
        {
            Order* order = readyTakeaway->peekFront();

            if (currentTime < order->readyTime + 1)
            { break;}

            order = readyTakeaway->dequeue();

            order->finishTime = currentTime;

            finishedOrders->enqueue(order);
        }
    
}
>>>>>>> shahd-chef-flow-phase2
