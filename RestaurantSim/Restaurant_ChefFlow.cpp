#include "Restaurant.h"

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
        }
    }
}

void Restaurant::MoveCookingToReady(int currentTime) {}
void Restaurant::FinalizeTakeawayOrders(int currentTime) {}