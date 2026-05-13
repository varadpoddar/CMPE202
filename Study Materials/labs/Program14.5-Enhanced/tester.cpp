#include <iostream>
#include <string>
#include "Ticket.h"

using namespace std;

void print(const string& name, const Ticket& ticket);

int main()
{
    Ticket ticket1(true, true, 2);
    print("John", ticket1);

    Ticket ticket2(true, false, 3);
    print("Mary", ticket2);

    Ticket ticket3(false, false, 0);
    print("Leslie", ticket3);

    Ticket ticket4(false, true, 1);
    print("Sidney", ticket4);

    return 0;
}

void print(const string& name, const Ticket& ticket)
{
    cout << endl;
    cout << name << "'s ticket:" << endl;
    cout << ticket;
    cout << "TOTAL COST: $" << ticket.get_cost() << endl;
}
