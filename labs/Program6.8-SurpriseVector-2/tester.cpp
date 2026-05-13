#include <iostream>
#include <vector>
#include "Appointments.h"
#include "Date.h"

using namespace std;

void print(const Appointments appts);

int main()
{
    cout << "TEST CONSTRUCTOR" << endl;
    Date d1969(1969, 7, 20);
    cout << "d1969: " << d1969 << endl;
    Date d2025(2025, 9,  2);
    cout << "d2025: " << d2025 << endl;
    Date d2027(2027, 4,  3);
    cout << "d2027: " << d2027 << endl;

    Appointments appts;

    cout << endl << "TEST APPEND" << endl;
    cout << "append d2025: " << d2025 << endl;
    appts.append(d2025);
    cout << "append d2027: " << d2027 << endl;
    appts.append(d2027);
    print(appts);

    cout << endl << "TEST INITIALIZATION" << endl;
    cout << "initialize d = d2025:" << endl;
    Date d = d2025;
    cout << d << endl;

    cout << endl << "TEST ASSIGNMENT" << endl;
    cout << "assign d = d2027:" << endl;
    d = d2027;
    cout << d << endl;

    cout << endl << "TEST INSERTION" << endl;
    cout << "insert " << d1969
         << " at index [0]:" << endl;
    appts.insert(0, d1969);
    print(appts);

    cout << endl << "TEST REMOVAL" << endl;
    cout << "remove " << appts.at(1)
         << " at index [1]:" << endl;
    appts.remove(1);
    print(appts);

    cout << endl << "Done!" << endl;
    return 0;
}

void print(const Appointments appts)
{
    int i = 0;

    cout << "printing vector ..." << endl;
    for (Date date : appts.get_dates())
    {
        cout << "[" << i << "] " << date << endl;
        i++;
    }
}
