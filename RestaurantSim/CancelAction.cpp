#include "CancelAction.h"
#include "Restaurant.h"

CancelAction::CancelAction(int time, int id) : Action(time), orderID(id) {}

void CancelAction::Execute(Restaurant* pRest) {
    pRest->CancelOrder(orderID);
}