#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>

#include "Order.h"
#include "Chef.h"
#include "Scooter.h"
#include "Table.h"
#include "Action.h"
#include "Queue.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "CookingQueue.h"
#include "FinishedOrders.h"

using namespace std;

class UI
{
public:
    UI();

    int getMode();

    void ClearScreen();
    void PrintHeader(int timestep);
    void PrintSection(const string& title);
    void WaitForKey();
    void WaitForMode(int mode);

    void PrintOrderQueueLine(const string& label, Queue<Order*>* q);
    void PrintTableQueueLine(const string& label, Queue<Table*>* q);
    void PrintActionQueueLine(const string& label, Queue<Action*>* q);

    void PrintChefLinkedLine(const string& label, LinkedQueue<Chef*>* q);
    void PrintScooterLinkedLine(const string& label, LinkedQueue<Scooter*>* q);

    void PrintOrderPriLine(const string& label, priQueue<Order*>* q);
    void PrintScooterPriLine(const string& label, priQueue<Scooter*>* q);

    void PrintFinishedLine(const string& label, FinishedOrders* finished);
};