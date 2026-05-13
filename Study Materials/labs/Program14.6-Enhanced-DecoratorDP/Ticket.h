#ifndef TICKET_H_
#define TICKET_H_

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Ticket
{
public:
    Ticket(const string desc, const double pr)
        : description(desc), price(pr)
    {
        cout << setw(17) << description
             << " price: $" << setw(2) << price << endl;
    }

    virtual ~Ticket() {}

    virtual double get_cost() const = 0;

    string get_description() const { return description; }

protected:
    string description;
    double price;
};

#endif /* TICKET_H_ */
