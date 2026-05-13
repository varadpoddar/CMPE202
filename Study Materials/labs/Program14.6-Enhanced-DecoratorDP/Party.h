#ifndef PARTY_H_
#define PARTY_H_

#include "Decorator.h"

const double PARTY_PRICE = 25;

class Party : public Decorator
{
public:
    Party(Ticket *ticket)
        : Decorator("pregame party", PARTY_PRICE, ticket) {}
};

#endif /* PARTY_H_ */
