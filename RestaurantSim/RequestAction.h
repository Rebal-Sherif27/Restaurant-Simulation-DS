#pragma once
#ifndef REQUESTACTION_H
#define REQUESTACTION_H

#include "Action.h"
#include <string>
using namespace std;

class RequestAction : public Action {
private:
    string orderType;
    int orderID;
    int size;
    int price;
    int seats;
    int duration;
    bool canShare;
    int distance;

public:
    RequestAction(int time, string type, int id, int sz, int pr, int st, int dur, bool share, int dist);
    void Execute(Restaurant* pRest) override;
};

#endif
