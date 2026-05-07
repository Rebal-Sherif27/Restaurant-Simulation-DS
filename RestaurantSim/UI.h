#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <chrono>

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

    void PrintSilentStart();
    void PrintSilentEnd();
};