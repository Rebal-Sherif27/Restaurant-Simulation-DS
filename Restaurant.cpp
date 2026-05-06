#include "Restaurant.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

Restaurant::Restaurant() {
    pendingOrders = new Queue<Order*>();
    cookingOrders = new CookingQueue();
    readyOrders = new Queue<Order*>();
    inServiceOrders = new priQueue<Order*>();
    finishedOrders = new Queue<Order*>();
    cancelledOrders = new Queue<Order*>();
    freeScooters = new priQueue<Scooter*>();
    backScooters = new priQueue<Scooter*>();
    maintScooters = new Queue<Scooter*>();
}

Restaurant::~Restaurant() {
    delete pendingOrders;
    delete cookingOrders;
    delete readyOrders;
    delete inServiceOrders;
    delete finishedOrders;
    delete cancelledOrders;
    delete freeScooters;
    delete backScooters;
    delete maintScooters;
}


void Restaurant::cancelOrder(int cancelID) {
    bool found = false;

    int size = pendingOrders->getCount();
    for (int i = 0; i < size; i++) {
        Order* temp = pendingOrders->dequeue();

        if (temp->id == cancelID) {
            cancelledOrders->enqueue(temp);
            std::cout << "SUCCESS: Order " << cancelID << " cancelled!" << std::endl;
            found = true;
        }
        else {
            pendingOrders->enqueue(temp);
        }
    }
    if (found) return;

    Order* cancelledCooking = cookingOrders->CancelOrder(cancelID);
    if (cancelledCooking != nullptr) {
        cancelledOrders->enqueue(cancelledCooking);
        std::cout << "SUCCESS: Order " << cancelID << " cancelled from cooking!" << std::endl;
    }
}

void Restaurant::SaveOutputFile(string filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Error: Unable to open output file!" << std::endl;
        return;
    }

    outFile << "FT\tID\tAT\tWT\tST\n";

    int totalOrders = 0, totalOD = 0, totalOV = 0;
    float sumWT = 0, sumST = 0;

    int size = finishedOrders->getCount();
    for (int i = 0; i < size; i++) {
        Order* pOrd = finishedOrders->dequeue();

        outFile << pOrd->finishTime << "\t"
            << pOrd->id << "\t"
            << pOrd->requestTime << "\t"
            << pOrd->waitTime << "\t"
            << pOrd->serviceTime << "\n";

        totalOrders++;
        sumWT += pOrd->waitTime;
        sumST += pOrd->serviceTime;

        if (pOrd->type == ODG || pOrd->type == ODN) totalOD++;
        else totalOV++;

        finishedOrders->enqueue(pOrd);
    }

    outFile << ".......................................................\n";
    outFile << ".......................................................\n";
    outFile << "Orders: " << totalOrders << " [OD:" << totalOD << ", OV:" << totalOV << "]\n";

    float avgWT = (totalOrders > 0) ? (sumWT / totalOrders) : 0;
    float avgST = (totalOrders > 0) ? (sumST / totalOrders) : 0;

    outFile << "Avg Wait = " << avgWT << ", Avg Serv = " << avgST << "\n";
    outFile.close();
}


void Restaurant::RunSimulation()
{
    std::cout << "Simulation started..." << std::endl;
    int timestep = 1;
    bool simulationDone = false;

    Order* testOrder = new Order(99, OVG, 1, 50, 1);
    testOrder->distance = 30;
    readyOrders->enqueue(testOrder);

    Scooter* testScooter = new Scooter(1, 10, 5, 3);
    freeScooters->enqueue(testScooter, testScooter->getSpeed());

    while (!simulationDone)
    {
        Scooter* returnedScooter;
        int returnTime;
        while (backScooters->peek(returnedScooter, returnTime) && (-returnTime) == timestep) {
            backScooters->dequeue(returnedScooter, returnTime);
            if (returnedScooter->needsMaintenance()) {
                returnedScooter->setMaintEndTime(timestep + returnedScooter->getMainDur());
                maintScooters->enqueue(returnedScooter);
            }
            else {
                freeScooters->enqueue(returnedScooter, returnedScooter->getSpeed());
            }
        }

        while (!maintScooters->isEmpty()) {
            Scooter* frontScooter = maintScooters->peekFront();
            if (frontScooter->getMaintEndTime() == timestep) {
                maintScooters->dequeue();
                frontScooter->resetOrderServed();
                freeScooters->enqueue(frontScooter, frontScooter->getSpeed());
            }
            else {
                break;
            }
        }

        int readySize = readyOrders->getCount();
        for (int i = 0; i < readySize; i++) {
            Order* pOrd = readyOrders->dequeue();

            if (pOrd->type == OVG || pOrd->type == OVC || pOrd->type == OVN) {
                if (!freeScooters->isEmpty()) {
                    Scooter* assignedScooter;
                    int scooterPri;
                    freeScooters->dequeue(assignedScooter, scooterPri);

                    pOrd->assignedScooter = assignedScooter;
                    pOrd->waitTime = timestep - pOrd->requestTime;
                    pOrd->serviceTime = (pOrd->distance + assignedScooter->getSpeed() - 1) / assignedScooter->getSpeed();
                    pOrd->finishTime = timestep + pOrd->serviceTime;

                    std::cout << "[Time " << timestep << "] Order " << pOrd->id << " assigned to Scooter " << assignedScooter->getID() << std::endl;
                    inServiceOrders->enqueue(pOrd, -(pOrd->finishTime));
                }
                else {
                    readyOrders->enqueue(pOrd);
                }
            }
            else {
                readyOrders->enqueue(pOrd); 
            }
        }

        if (timestep > 100) simulationDone = true;
        timestep++;
    }

    SaveOutputFile("output.txt");
    std::cout << "Simulation finished successfully!" << std::endl;
}