#include "UI.h"
#include <iostream>
#include <conio.h>
using namespace std;

void UI::PrintPhase1Screen(int timestep,
    Queue<Order*>* pending,
    Queue<Order*>* ready,
    priQueue<Order*>* service,
    Queue<Order*>* finished)
{
    system("cls");

    cout << "----------------- RESTAURANT SIMULATION-----------------" << endl;
    cout << "Current Timestep: " << timestep << endl;
    cout << "--------------------------------------------------------" << endl;

    cout << endl << "[Pending orders]: ";
    pending->printIDs();

    cout << endl << "[Ready orders]: ";
    ready->printIDs();

    cout << endl << "[In-Service Orders]: ";
    service->printIDs(); // We'll add this to priQueue.h in a second

    cout << endl << "[Finished orders]: ";
    finished->printIDs();

    // ... add the rest similarly ...
}

void UI::WaitForKey()
{
    std::cout << std::endl << "Press any key to move to next step..." << std::endl;
    (void)_getch(); // The (void) cast tells the compiler you are intentionally ignoring it.
}

int UI::getMode() {
    int choice;
    cout << "Select Simulation Mode:" << endl;
    cout << "1. Interactive Mode - 2. Step-by-Step Mode - 3. Silent Mode" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    return choice;
}

