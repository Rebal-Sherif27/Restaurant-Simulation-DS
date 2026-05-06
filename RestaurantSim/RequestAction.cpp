#include "RequestAction.h"
#include "Restaurant.h"
#include "Order.h"
#include <map>

static map<string, OrderType> strToType = {
    {"ODG", ODG}, {"ODN", ODN}, {"OT", OT}, {"OVG", OVG}, {"OVC", OVC}, {"OVN", OVN}
};

RequestAction::RequestAction(int time, string type, int id, int sz, int pr, int st, int dur, bool share, int dist)
    : Action(time), orderType(type), orderID(id), size(sz), price(pr), seats(st), duration(dur), canShare(share), distance(dist) {
}

void RequestAction::Execute(Restaurant* pRest) {
    OrderType ot = strToType[orderType];
    Order* o = new Order(actionTime, orderID, ot, size, price, seats, duration, canShare, distance);

    if (orderType == "ODG") pRest->addPendingODG(o);
    else if (orderType == "ODN") pRest->addPendingODN(o);
    else if (orderType == "OT") pRest->addPendingOT(o);
    else if (orderType == "OVG") pRest->addPendingOVG(o);
    else if (orderType == "OVC") pRest->addPendingOVC(o);
    else if (orderType == "OVN") pRest->addPendingOVN(o);
}
