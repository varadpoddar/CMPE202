#ifndef DECORATOR_H_
#define DECORATOR_H_

#include <string>
#include "Ticket.h"

using namespace std;

class Decorator : public Ticket
{
public:
    Decorator(const string description, const double price,
              Ticket *tckt)
        : Ticket(description, price), ticket(tckt) {}

    virtual ~Decorator() { delete ticket; }

    double get_cost() const override
    {
        return price + ticket->get_cost();
    }

private:
    Ticket *ticket;
};

#endif /* DECORATOR_H_ */
