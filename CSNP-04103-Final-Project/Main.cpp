/***************************************************************
* Name: Aidan Sharpe, Jason Mendolera
* Course: Computer Science & Programming
* Class: CS04103 Section: 6
* Assignment Date: <date>
* File Name: main.cpp
*****************************************************************
* ID: Final Project
* Purpose: Restaraunt table reservation system
*****************************************************************/

#include <iostream>
#include "Table.h"
#include <string>
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

vector<Table> setupRestaurant();
string formatTime(int);
bool processCommand(string);
void runGui();
void runMainLoop();

vector<Table> tables;                   // list of the tables at the restaurant
int main()
{
    tables = setupRestaurant();         // create new restaurant

    runMainLoop();
    // thread gui(runGui);
    // thread control(runMainLoop);
    // 
    // gui.join();
    // control.join();
    
    return 0;
}

vector<Table> setupRestaurant()
{
    int tableCount;
    vector<Table> tables;

    cout << "How many tables are in your restaraunt? ";
    cin >> tableCount;

    for (int i = 0; i < tableCount; i++)
    {
        int size;
        cout << "Size of table #" << i + 1 << ": ";
        cin >> size;
        tables.push_back(Table(size));
    }

    return tables;
}

// convert UNIX Epoch timestamp to 12-hour time
string formatTime(int timestamp)
{
    const int S2021 = 1609477200, DAY = 86400, HOUR = 3600, MIN = 60, TIMEZONE = -5;
    int days, hours, mins, secs;
    string h, m, s;

    days = timestamp / DAY;                                                         // find the number of days since 1970.01.01 00:00:00 GMT
    timestamp -= days * DAY;                                                          // subtract that number of days worth of seconds
    hours = timestamp / HOUR;                                                       // find the number of hours remaining
    timestamp -= hours * HOUR;                                                        // subtract that number of hours in seconds
    mins = timestamp / MIN;                                                         // find the number of minutes remaining
    timestamp -= mins * MIN;                                                          // subtrace that number of minutes in seconds
    secs = timestamp;                                                               // only seconds remain

    h = to_string(abs((hours + TIMEZONE) % 12));                                    // convert to 12-hour time
    m = (to_string(mins).length() == 1 ? '0' + to_string(mins) : to_string(mins));  // add a leading 0 to minutes, if neccessary
    s = (to_string(secs).length() == 1 ? '0' + to_string(secs) : to_string(secs));  // add a leading 0 to seconds, if neccessary
    return  h + ':' + m + ':' + s;
}

bool processCommand(string cmd)
{
    string arg;
    int argpos = cmd.find(' ') + 1;

    if (argpos != 0)
    {
        arg = cmd.substr(argpos);
        cmd = cmd.substr(0, argpos);

        cout << cmd << endl << arg << endl;
    }

    if (cmd == "close")
        return false;
    else if (cmd == "reserve")
    {
        cin >> arg;
        // reserve table #<arg> if it has not been reserved already
        if (tables.at(stoi(arg) - 1).reserve())
            cout << "Reserved table #" << arg << endl;
        else
            cout << "Table #" << arg << " is already reserved." << endl;
    }
    else if (cmd == "table")
    {
        cin >> arg;
        if (tables.at(stoi(arg) - 1).isReserved())
            cout << "Table #" << arg << " was reserved at " << formatTime(tables.at(stoi(arg) - 1).when()) << endl;
        else
            cout << "Table #" << arg << " is not reserved." << endl;
    }
    else if (cmd == "clear")
    {
        cin >> arg;
        // remove the reservation from table #<arg> if there is one
        if (arg == "all")
        {
            for (int i = 0; i < tables.size(); i++)
                tables.at(i).clean();
            cout << "Cleared all tables." << endl;
        }
        else
            if (tables.at(stoi(arg) - 1).clean())
                cout << "Cleared table #" << arg << endl;
            else
                cout << "Table #" << arg << " has already been cleaned." << endl;
    }

    else if (cmd == "party")
    {
        cin >> arg;
        bool reserved = false;
        // find a table of size <arg> and reserve it 
        for (int i = 0; i < tables.size(); i++)
            if ((tables.at(i).getSize() == stoi(arg) || tables.at(i).getSize() == stoi(arg) + 1) && tables.at(i).reserve())
            {
                reserved = true;
                break;
            }
        if (!reserved)
            cout << "No tables available for " << arg << " people.";
    }
    else if (cmd == "res-time")
    {
        cin >> arg;
        if (tables.at(stoi(arg) - 1).isReserved())
            cout << "Table #" << arg << " was reserved at " << formatTime(tables.at(stoi(arg) - 1).when()) << endl;
    }
    else if (cmd == "help")
    {
        cout << "************************** Help Menu *******************************" << endl
            << "close        >>>  Close the restaurant and stop asking for commands." << endl
            << "reserve <n>  >>>  Reserve table n." << endl
            << "clear <n>    >>>  Prepare table n for the next customer." << endl
            << "party <n>    >>>  Find and reserve a table for a party of n people." << endl;
    }
    // else
    // {
    //     cout << "Invalid command. Type \"help\" to view the list of valid commands." << endl;
    // }
    return true;
}

void runGui()
{
    
}

void runMainLoop()
{
    bool open = true;
    string cmd;
    ifstream r;
    ofstream w;

    while (open)
    {
        cout << ">>> ";
        cin >> cmd;
        open = processCommand(cmd);
    }
}