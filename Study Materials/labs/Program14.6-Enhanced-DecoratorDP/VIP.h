#ifndef VIP_H_
#define VIP_H_

#include "Decorator.h"

const double VIP_PRICE = 20;

class VIP : public Decorator
{
public:
    VIP(Ticket *ticket)
        : Decorator("VIP seating", VIP_PRICE, ticket) {}
};

#endif /* VIP_H_ */
