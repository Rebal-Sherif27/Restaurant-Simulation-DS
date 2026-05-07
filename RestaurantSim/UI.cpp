#include "UI.h"

UI::UI()
{}

int UI::getMode()
{
    int choice;

    cout << "==============================================" << endl;
    cout << "        RESTAURANT SIMULATION SYSTEM          " << endl;
    cout << "==============================================" << endl;
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
    cout << "============================================================" << endl;
    cout << "              RESTAURANT SIMULATION SYSTEM                  " << endl;
    cout << "============================================================" << endl;
    cout << "Current Timestep: " << timestep << endl;
    cout << "============================================================" << endl;
}

void UI::PrintSection(const string& title)
{
    cout << endl;
    cout << "---------------- " << title << " ----------------" << endl;
}

void UI::WaitForKey()
{
    cout << endl;
    cout << "Press any key to move to the next timestep..." << endl;
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

void UI::PrintOrderQueueLine(const string& label, Queue<Order*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    Queue<Order*> temp;
    Order* ord;

    while (!q->isEmpty())
    {
        ord = q->dequeue();

        if (ord)
            cout << ord->id << " ";

        temp.enqueue(ord);
    }

    while (!temp.isEmpty())
    {
        q->enqueue(temp.dequeue());
    }

    cout << endl;
}

void UI::PrintTableQueueLine(const string& label, Queue<Table*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    Queue<Table*> temp;
    Table* table;

    while (!q->isEmpty())
    {
        table = q->dequeue();

        if (table)
            cout << table->getTabelID() << " ";

        temp.enqueue(table);
    }

    while (!temp.isEmpty())
    {
        q->enqueue(temp.dequeue());
    }

    cout << endl;
}

void UI::PrintActionQueueLine(const string& label, Queue<Action*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    Queue<Action*> temp;
    Action* act;

    while (!q->isEmpty())
    {
        act = q->dequeue();

        if (act)
            cout << "[T=" << act->GetActionTime() << "] ";

        temp.enqueue(act);
    }

    while (!temp.isEmpty())
    {
        q->enqueue(temp.dequeue());
    }

    cout << endl;
}

void UI::PrintChefLinkedLine(const string& label, LinkedQueue<Chef*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    LinkedQueue<Chef*> temp;
    Chef* chef;

    while (q->dequeue(chef))
    {
        if (chef)
            cout << chef->GetID() << " ";

        temp.enqueue(chef);
    }

    while (temp.dequeue(chef))
    {
        q->enqueue(chef);
    }

    cout << endl;
}

void UI::PrintScooterLinkedLine(const string& label, LinkedQueue<Scooter*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    LinkedQueue<Scooter*> temp;
    Scooter* scooter;

    while (q->dequeue(scooter))
    {
        if (scooter)
            cout << scooter->getID() << " ";

        temp.enqueue(scooter);
    }

    while (temp.dequeue(scooter))
    {
        q->enqueue(scooter);
    }

    cout << endl;
}

void UI::PrintOrderPriLine(const string& label, priQueue<Order*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    priQueue<Order*> temp;
    Order* ord;
    int pri;

    while (q->dequeue(ord, pri))
    {
        if (ord)
            cout << ord->id << " ";

        temp.enqueue(ord, pri);
    }

    while (temp.dequeue(ord, pri))
    {
        q->enqueue(ord, pri);
    }

    cout << endl;
}

void UI::PrintScooterPriLine(const string& label, priQueue<Scooter*>* q)
{
    cout << left << setw(35) << label << ": ";

    if (!q || q->isEmpty())
    {
        cout << "None" << endl;
        return;
    }

    priQueue<Scooter*> temp;
    Scooter* scooter;
    int pri;

    while (q->dequeue(scooter, pri))
    {
        if (scooter)
            cout << scooter->getID() << " ";

        temp.enqueue(scooter, pri);
    }

    while (temp.dequeue(scooter, pri))
    {
        q->enqueue(scooter, pri);
    }

    cout << endl;
}

void UI::PrintFinishedLine(const string& label, FinishedOrders* finished)
{
    cout << left << setw(35) << label << ": ";

    if (!finished)
    {
        cout << "None" << endl;
        return;
    }

    finished->printIDs();
    cout << endl;
}