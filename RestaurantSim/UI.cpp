#include "UI.h"
#include <iostream>
#include <conio.h>
using namespace std;

void UI::PrintPhase1Screen(int timestep)
{
    system("cls");

    cout << "----------------- RESTAURANT SIMULATION-----------------" << endl;
    cout << "Current Timestep: " << timestep << endl;
    cout << "--------------------------------------------------------" << endl;

    cout << endl << "[Pending orders]" << endl;
    cout << endl << "[Available Chefs]" << endl;
    cout << endl << "[Cooking orders]" << endl;
    cout << endl << "[Ready orders]" << endl;
    cout << endl << "[In-Service Orders]" << endl;
    cout << endl << "[Finished orders]" << endl;
    cout << endl << "[Cancelled orders]" << endl;
    cout << endl << "[Scooters]" << endl;
    cout << endl << "[Tables]" << endl;
    cout << endl << "[Maintenance]" << endl;}

void UI::WaitForKey()
{
    cout << endl;
    cout << "Press any key to move to next step..." << endl;
    _getch();
}

int UI::getMode() {
    int choice;
    cout << "Select Simulation Mode:" << endl;
    cout << "1. Interactive Mode - 2. Step-by-Step Mode - 3. Silent Mode" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    return choice;
}