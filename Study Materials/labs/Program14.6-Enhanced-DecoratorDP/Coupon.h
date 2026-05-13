#ifndef COUPON_H_
#define COUPON_H_

#include "Decorator.h"

const double COUPON_PRICE = 5;

class Coupon : public Decorator
{
public:
    Coupon(Ticket *ticket)
        : Decorator("drink coupon", COUPON_PRICE, ticket) {}
};

#endif /* COUPON_H_ */
