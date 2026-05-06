#include "Restaurant.h"
#include<cmath>

void Restaurant::AssignPendingToChef(int currentTime)
{

        while (!pendingODG->isEmpty() && !freeCS->isEmpty())
        {
            Order* order = pendingODG->dequeue();
            Chef* chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

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
        }
}


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