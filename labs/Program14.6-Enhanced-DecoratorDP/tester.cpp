#include <iostream>
#include <iomanip>

#include "BaseTicket.h"
#include "Party.h"
#include "VIP.h"
#include "Coupon.h"

using namespace std;

void print(const string name, const Ticket * const ticket);

int main()
{
    Ticket *ticket = new BaseTicket();
    ticket = new Party(ticket);
    ticket = new VIP(ticket);
    ticket = new Coupon(ticket);
    ticket = new Coupon(ticket);

    print("John", ticket);
    delete ticket;

    ticket = new BaseTicket();
    ticket = new Coupon(ticket);
    ticket = new Coupon(ticket);
    ticket = new Party(ticket);
    ticket = new Coupon(ticket);

    print("Mary", ticket);
    delete ticket;

    ticket = new BaseTicket();

    print("Leslie", ticket);
    delete ticket;

    ticket = new BaseTicket();
    ticket = new Coupon(ticket);
    ticket = new VIP(ticket);

    print("Sidney", ticket);
    delete ticket;

    return 0;
}

void print(const string name, const Ticket * const ticket)
{
    cout << endl;
    cout << setw(26) << name + "'s ticket TOTAL: $"
         << ticket->get_cost() << endl;
    cout << "----------------------------" << endl;
}
