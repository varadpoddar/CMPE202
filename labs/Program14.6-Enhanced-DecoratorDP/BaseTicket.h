#ifndef BASETICKET_H_
#define BASETICKET_H_

#include "Ticket.h"

const double BASE_PRICE = 30;

class BaseTicket : public Ticket
{
public:
    BaseTicket() : Ticket("base ticket", BASE_PRICE) {}

    double get_cost() const override { return BASE_PRICE; }
};

#endif /* BASETICKET_H_ */
