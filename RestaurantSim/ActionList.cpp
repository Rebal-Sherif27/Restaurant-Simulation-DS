#include "ActionList.h"
#include "Restaurant.h"
#include "RequestAction.h"
#include "CancelAction.h"
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