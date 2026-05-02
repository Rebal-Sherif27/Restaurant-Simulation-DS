#include "Table.h"
#include "Order.h"

using namespace std;

Table::Table(int id, int cap, bool sharable)
    : tabelID(id)
    , capacity(cap)
    , currentload(0)
    , issharable(sharable)
    , currentorder(nullptr)
    , isReserved(false)
{
}

void Table::assignorder(Order* neworder) {
    currentorder = neworder;
    currentload = neworder->getNumPeople();
}

void Table::freeTable() {
    currentorder = nullptr;
    currentload = 0;
    // You may need to store the "original" sharability in a separate 
    // variable like 'originalSharable' if you want to reset it properly here.
}

void Table::setSharable(bool status) {
    issharable = status;
}

int Table::getCapacity() const {
    return capacity;
}

int Table::getCurrentload() const {
    return currentload;
}

bool Table::isSharable() const {
    return issharable;
}

int Table::getTabelID() const {
    return tabelID;
}

void Table::setCurrentload(int load) {
    currentload = load;
}
