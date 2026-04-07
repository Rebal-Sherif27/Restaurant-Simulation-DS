#include "ActionList.h"
#include "Restaurant.h"
#include <iostream>

ActionList::ActionList() {}

ActionList::~ActionList() {
    while (!actionsQueue.isEmpty()) {
        Action* pAct = actionsQueue.dequeue();
        delete pAct;
    }
}

void ActionList::AddAction(Action* pAct) {
    actionsQueue.enqueue(pAct);
}

void ActionList::ExecuteActions(int currentTime, Restaurant* pRest) {
    while (!actionsQueue.isEmpty()) {
        Action* pAct = actionsQueue.peekFront();

        if (pAct->GetActionTime() == currentTime) {
            pAct = actionsQueue.dequeue();
            pAct->Execute(pRest);
            delete pAct;
        }
        else {
            break;
        }
    }
}

RequestAction::RequestAction(int time, Order* o) : Action(time) {
    pOrd = o;
}

void RequestAction::Execute(Restaurant* pRest) {
    if (pOrd->type == ODG) {
        pRest->addPendingODG(pOrd);
    }
    else if (pOrd->type == ODN) {
        pRest->addPendingODN(pOrd);
    }
    else if (pOrd->type == OT) {
        pRest->addPendingOT(pOrd);
    }
    else if (pOrd->type == OVG) {
        pRest->addPendingOVG(pOrd);
    }
    else if (pOrd->type == OVC) {
        pRest->addPendingOVC(pOrd);
    }
    else if (pOrd->type == OVN) {
        pRest->addPendingOVN(pOrd);
    }
}

CancelAction::CancelAction(int time, int id) : Action(time) {
    orderID = id;
}

void CancelAction::Execute(Restaurant* pRest) {
    bool removed = false;

    removed = pRest->RemoveFromPendingOVC(orderID);
    if (removed) {
        std::cout << "Timestep " << actionTime << ": Order #" << orderID << " cancelled from pending\n";
        return;
    }

    removed = pRest->RemoveFromCookingOVC(orderID);
    if (removed) {
        pRest->ReleaseChefFromOrder(orderID);
        std::cout << "Timestep " << actionTime << ": Order #" << orderID << " cancelled from cooking\n";
        return;
    }

    removed = pRest->RemoveFromReadyOVC(orderID);
    if (removed) {
        std::cout << "Timestep " << actionTime << ": Order #" << orderID << " cancelled from ready\n";
        return;
    }
}
