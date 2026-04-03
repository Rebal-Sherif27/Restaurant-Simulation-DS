#include "ActionList.h"
#include "Restaurant.h"
#include <iostream>

ActionList::ActionList() {}

void ActionList::AddAction(Action* pAct) {
    actionsQueue.enqueue(pAct);
}

void ActionList::ExecuteActions(int currentTime, Restaurant* pRest) {
    while (!actionsQueue.isEmpty()) {
        Action* pAct = actionsQueue.peekFront();
        
        // Only execute if it's the right time
        if (pAct->GetActionTime() == currentTime) {
            pAct = actionsQueue.dequeue();
            pAct->Execute(pRest);
            delete pAct; // Clean up the action object
        } else {
            break; 
        }
    }
}

// --- Request Action Implementation ---
RequestAction::RequestAction(int time, Order* o) : Action(time) {
    pOrd = o;
}

void RequestAction::Execute(Restaurant* pRest) {
    // Based on Phase 1.2, move the order to the correct Pending List
    if (pOrd->type == GRILLED) {
        pRest->addGrilledOrder(pOrd);
    } 
    else if (pOrd->type == OVC) {
        // This is your OVC (Delivery Cold) list
        pRest->addOVCOrder(pOrd); 
    }
    else {
        pRest->addNormalOrder(pOrd);
    }
}

// --- Cancel Action Implementation ---
CancelAction::CancelAction(int time, int id) : Action(time) {
    orderID = id;
}

void CancelAction::Execute(Restaurant* pRest) {
    // Phase 1.2: ONLY OVC orders can be cancelled
    // We look into the OVC Pending list (Cancelled_orders list)
    bool removed = pRest->RemoveFromOVCPending(orderID);
    
    if (removed) {
        std::cout << "Timestep " << ActionTime << ": Order #" << orderID << " cancelled.\n";
    }
}
