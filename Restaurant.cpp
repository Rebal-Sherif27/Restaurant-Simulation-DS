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

// =================================================================
// TASK 1: Cancellation Logic (Pending, Cooking, Ready)
// =================================================================
void Restaurant::cancelOrder(int cancelID) {
    bool found = false;

    // 1. Check Pending Orders
    int size = pendingOrders->getCount();
    for (int i = 0; i < size; i++) {
        Order* temp = pendingOrders->dequeue();

        if (!found && temp->id == cancelID) {
            cancelledOrders->enqueue(temp);
            std::cout << "[CHECK] SUCCESS: Order " << cancelID << " was cancelled from Pending Queue!" << std::endl;
            found = true;
        }
        else {
            pendingOrders->enqueue(temp);
        }
    }
    if (found) return;

    // 2. Check Cooking Orders
    Order* cancelledCooking = cookingOrders->CancelOrder(cancelID);
    if (cancelledCooking != nullptr) {
        cancelledOrders->enqueue(cancelledCooking);
        std::cout << "[CHECK] SUCCESS: Order " << cancelID << " was cancelled from Cooking Queue!" << std::endl;

        // ---> TODO for teammate integration: FREE THE CHEF HERE <---
        // Example: cancelledCooking->assignedChef->setFree(true);
        found = true;
    }
    if (found) return;

    // 3. Check Ready Orders
    size = readyOrders->getCount();
    for (int i = 0; i < size; i++) {
        Order* temp = readyOrders->dequeue();

        if (!found && temp->id == cancelID) {
            cancelledOrders->enqueue(temp);
            std::cout << "[CHECK] SUCCESS: Order " << cancelID << " was cancelled from Ready Queue!" << std::endl;
            found = true;
        }
        else {
            readyOrders->enqueue(temp);
        }
    }
}

// =================================================================
// TASK 2: Output File Logic
// =================================================================
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
    std::cout << "[CHECK] Output file generated successfully as " << filename << std::endl;
}

void Restaurant::RunSimulation()
{
    std::cout << "Simulation started..." << std::endl;
    int timestep = 1;
    bool simulationDone = false;

    // =================================================================
    // TEMPORARY DUMMY DATA (To trigger your checks)
    // =================================================================
    // Put an order in Ready and a Scooter in Free
    Order* testOrder = new Order(99, OVG, 1, 50, 1);
    testOrder->distance = 30;
    readyOrders->enqueue(testOrder);

    Scooter* testScooter = new Scooter(1, 10, 5, 3);
    freeScooters->enqueue(testScooter, testScooter->getSpeed());

    // Put an order in Ready that we will cancel at timestep 2
    Order* cancelTestOrder = new Order(55, OVC, 2, 100, 1);
    readyOrders->enqueue(cancelTestOrder);
    // =================================================================

    while (!simulationDone)
    {
        // Trigger Cancellation Check
        if (timestep == 2) {
            std::cout << "\n[Time 2] Attempting to cancel Order 55..." << std::endl;
            cancelOrder(55);
        }

        // =================================================================
        // TASK: Check Returning Scooters (Back -> Free/Maintenance)
        // =================================================================
        Scooter* returnedScooter;
        int returnPri;

        // We use negative return time as priority, so check if top scooter is arriving now
        while (backScooters->peek(returnedScooter, returnPri) && (-returnPri) == timestep) {
            backScooters->dequeue(returnedScooter, returnPri);

            std::cout << "[Time " << timestep << "] [CHECK] Scooter " << returnedScooter->getID() << " returned to the restaurant!" << std::endl;

            if (returnedScooter->needsMaintenance()) {
                returnedScooter->setMaintEndTime(timestep + returnedScooter->getMainDur());
                maintScooters->enqueue(returnedScooter);
                std::cout << "          -> It needs maintenance! Going to maintScooters until time " << returnedScooter->getMaintEndTime() << std::endl;
            }
            else {
                freeScooters->enqueue(returnedScooter, returnedScooter->getSpeed());
                std::cout << "          -> It's good to go! Going back to freeScooters." << std::endl;
            }
        }

        // =================================================================
        // TASK 3: Process Scooter Maintenance (Maint -> Free)
        // =================================================================
        while (!maintScooters->isEmpty()) {
            Scooter* frontScooter = maintScooters->peekFront();
            if (frontScooter->getMaintEndTime() == timestep) {
                maintScooters->dequeue();
                frontScooter->resetOrderServed();
                freeScooters->enqueue(frontScooter, frontScooter->getSpeed());
                std::cout << "[Time " << timestep << "] [CHECK] Scooter " << frontScooter->getID() << " finished maintenance and is back to free scooters!" << std::endl;
            }
            else {
                break;
            }
        }

        // =================================================================
        // TASK: Check Finished Deliveries (In-Service -> Finished)
        // =================================================================
        Order* finishedOrd;
        int negFinishTime;

        // Peak at the top of In-Service. Priority is -finishTime.
        while (inServiceOrders->peek(finishedOrd, negFinishTime) && (-negFinishTime) == timestep) {
            inServiceOrders->dequeue(finishedOrd, negFinishTime);
            finishedOrders->enqueue(finishedOrd);

            // Calculate scooter return time and push to backScooters
            Scooter* s = finishedOrd->assignedScooter;
            s->increaseOrderServed();

            int returnDuration = (finishedOrd->distance + s->getSpeed() - 1) / s->getSpeed();
            int returnTime = timestep + returnDuration;

            // Enqueue with negative return time so the earliest returning is at the top!
            backScooters->enqueue(s, -returnTime);

            std::cout << "[Time " << timestep << "] [CHECK] Order " << finishedOrd->id << " delivered! Scooter " << s->getID() << " is driving back. Will return at Time " << returnTime << std::endl;
        }

        // =================================================================
        // TASK 4: Stage 2 Assignments (Ready -> In-Service)
        // =================================================================
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

                    std::cout << "[Time " << timestep << "] [CHECK] Order " << pOrd->id << " assigned to Scooter " << assignedScooter->getID() << " (Finishing at Time " << pOrd->finishTime << ")" << std::endl;

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

        // Stop the simulation after 10 timesteps so we can see the full cycle!
        if (timestep > 10) simulationDone = true;
        timestep++;
    }

    std::cout << "\n";
    SaveOutputFile("output.txt");
    std::cout << "Simulation finished successfully!" << std::endl;
}