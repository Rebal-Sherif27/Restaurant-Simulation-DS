#pragma once
class Restaurant;

class Action {
protected:
    int actionTime;
public:
    Action(int time) : actionTime(time) {}
    virtual ~Action() {}
    int GetActionTime() const { return actionTime; }
    virtual void Execute(Restaurant* pRest) = 0;
};
