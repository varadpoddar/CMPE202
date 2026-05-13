#ifndef TICKET_H_
#define TICKET_H_

#include <iostream>
#include <iomanip>

using namespace std;

class Ticket
{
public:
    Ticket(const bool party, const bool vip, const int coupons)
       : pregame_party(party), vip_seating(vip),
         drink_coupons(coupons) {}

    double get_cost() const
    {
       double total = BASE_PRICE;

       if (pregame_party) total += PARTY_PRICE;
       if (vip_seating)   total += VIP_PRICE;

       return total + drink_coupons*COUPON_PRICE;
    }

    friend ostream& operator <<(ostream& ostr, const Ticket& ticket);

private:
    bool pregame_party;
    bool vip_seating;
    int  drink_coupons;

    double const BASE_PRICE   = 30;
    double const PARTY_PRICE  = 25;
    double const VIP_PRICE    = 20;
    double const COUPON_PRICE =  5;
};

inline ostream& operator <<(ostream& ostr, const Ticket& ticket)
{
    ostr << setw(24) << "base ticket price: $"
         << setw(2)  << ticket.BASE_PRICE << endl;

    if (ticket.pregame_party)
    {
        ostr << setw(24) << "pregame party price: $"
             << setw(2) << ticket.PARTY_PRICE << endl;
    }

    if (ticket.vip_seating)
    {
        ostr << setw(24) << "VIP seating price: $"
             << setw(2)  << ticket.VIP_PRICE << endl;
    }

    int count = ticket.drink_coupons;

    if (count > 0)
    {
        ostr << setw(24) << "drink coupon price: $"
             << setw(2)  << count*ticket.COUPON_PRICE
             << " = " << count << " x $"
             << ticket.COUPON_PRICE << endl;
    }

    return ostr;
}

#endif /* TICKET_H_ */
