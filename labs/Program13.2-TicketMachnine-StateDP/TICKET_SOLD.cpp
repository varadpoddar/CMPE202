#include <iostream>
#include "Enums.h"
#include "State.h"
#include "StatesBlock.h"

using namespace std;

State *TICKET_SOLD::insert_credit_card()  // Action 1
{
    cout << "Take the ticket you've already bought."
         << endl;

    card_inserted = true;
    card_validity = Validity::UNKNOWN;
    return this;
}

State *TICKET_SOLD::check_validity()  // Action 2
{
    cout << "Take the ticket that you've already bought. "
         << endl;

    return this;
}

State *TICKET_SOLD::take_ticket()  // Action 3
{
    cout << "Remove your credit card. "
         << "Enjoy the game!" << endl;

    count--;

    if (count > 0)
    {
        return states.READY_state;
    }
    else
    {
        return states.SOLD_OUT_state;
    }
}

State *TICKET_SOLD::remove_credit_card()  // Action 4
{
    cout << "First take your ticket." << endl;

    return this;
}
