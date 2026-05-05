#pragma once
#ifndef CANCELACTION_H
#define CANCELACTION_H

#include "Action.h"

class CancelAction : public Action {
private:
    int orderID;
public:
    CancelAction(int time, int id);
    void Execute(Restaurant* pRest) override;
};

#endif
