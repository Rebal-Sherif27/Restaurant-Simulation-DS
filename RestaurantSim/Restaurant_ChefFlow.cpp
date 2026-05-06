#include "Restaurant.h"
using namespace std;

void Restaurant::AssignPendingToChef(int currentTime)
{

        while (!pendingODG->isEmpty() && !freeCS->isEmpty())
        {
            Order* order = pendingODG->dequeue();
            Chef* chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = (order->size + chef->GetSpeed() - 1) / chef->GetSpeed();
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

            int cookTime = (order->size + chef->GetSpeed() - 1) / chef->GetSpeed();
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingOT->isEmpty() && !freeCN->isEmpty())
        {
            Order* order = pendingOT->dequeue();
            Chef* chef = freeCN->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = (order->size + chef->GetSpeed() - 1) / chef->GetSpeed();
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }

        while (!pendingOVG->isEmpty() && !freeCS->isEmpty())
        {
            Order* order = pendingOVG->dequeue();
            Chef* chef = freeCS->dequeue();

            order->assignedChef = chef;
            order->assignTime = currentTime;

            int cookTime = (order->size + chef->GetSpeed() - 1) / chef->GetSpeed();
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

            int cookTime = (order->size + chef->GetSpeed() - 1) / chef->GetSpeed();
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

            int cookTime = (order->size + chef->GetSpeed() - 1) / chef->GetSpeed();
            order->readyTime = currentTime + cookTime;

            cookingOrders->enqueue(order, 100000 - order->readyTime);
        }
}


void Restaurant::MoveCookingToReady(int currentTime)
{
    // Feature 9
}

void Restaurant::FinalizeTakeawayOrders(int currentTime)
{
    // Feature 12
}