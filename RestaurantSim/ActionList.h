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

class RequestAction : public Action {
    Order* pOrd;
public:
    RequestAction(int time, Order* o);
    virtual void Execute(Restaurant* pRest);
};

class CancelAction : public Action {
    int orderID;
public:
    CancelAction(int time, int id);
    virtual void Execute(Restaurant* pRest);
};

