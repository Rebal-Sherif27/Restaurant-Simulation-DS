#include "UI.h"

UI::UI()
{}

int UI::getMode()
{
    int choice;

    cout << "====================================================" << endl;
    cout << "             RESTAURANT SIMULATION SYSTEM           " << endl;
    cout << "====================================================" << endl;
    cout << "Select Simulation Mode:" << endl;
    cout << "1. Interactive Mode" << endl;
    cout << "2. Step-by-Step Mode" << endl;
    cout << "3. Silent Mode" << endl;
    cout << "Enter your choice (1-3): ";

    cin >> choice;

    while (choice < 1 || choice > 3)
    {
        cout << "Invalid choice. Enter 1, 2, or 3: ";
        cin >> choice;
    }

    return choice;
}

void UI::ClearScreen()
{
    system("cls");
}

void UI::PrintHeader(int timestep)
{
    cout << "Current Timestep:" << timestep << endl;
}

void UI::PrintSection(const string& title)
{
    cout << endl;
    cout << "---------------- " << title << " ----------------" << endl;
}

void UI::WaitForKey()
{
    cout << endl;
    cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
    _getch();
}

void UI::WaitForMode(int mode)
{
    if (mode == 1)
    {
        WaitForKey();
    }
    else if (mode == 2)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void UI::PrintSilentStart()
{
    cout << "Simulation Starts in Silent mode ..." << endl;
}

void UI::PrintSilentEnd()
{
    cout << "Simulation ends, Output file created" << endl;
}