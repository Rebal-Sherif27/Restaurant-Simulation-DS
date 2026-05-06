#pragma once
#include "Queue.h"
#include "Action.h"
#include "Order.h"

class Restaurant;

class ActionList {
private:
    Queue<Action*> actionsQueue;

public:
    ActionList();
    ~ActionList();

    void AddAction(Action* pAct);
    void ExecuteActions(int currentTime, Restaurant* pRest);
};