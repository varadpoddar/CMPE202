#include <iostream>
#include "Enums.h"
#include "State.h"
#include "StatesBlock.h"

using namespace std;

State *VALIDATING::insert_credit_card()  // Action 1
{
    if (card_validity == Validity::NO)
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;

        return states.READY_state;
    }
    else
    {
        cout << "You've already inserted your credit card. "
             << "Checking its validation." << endl;

        return this;
    }
}

State *VALIDATING::check_validity()  // Action 2
{
    if (card_validity == Validity::UNKNOWN)
    {
        bool valid = rand()%4 > 0;
        card_validity = valid ? Validity::YES : Validity::NO;
    }

    if (card_validity == Validity::YES)
    {
        cout << "Your credit card is validated. "
             << "Take your ticket." << endl;

        return states.TICKET_SOLD_state;
    }
    else
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;

        return states.READY_state;
    }
}

State *VALIDATING::take_ticket()  // Action 3
{
    if (card_validity == Validity::UNKNOWN)
    {
        cout << "Still checking your credit card's validity."
             << endl;
    }
    else if (card_validity == Validity::YES)
    {
        cout << "Your card is already validated. "
             << "Take your ticket." << endl;
    }
    else
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;
    }

    return this;
}

State *VALIDATING::remove_credit_card()  // Action 4
{
    if (!card_inserted)
    {
        cout << "No credit card inserted." << endl;
    }
    else if (card_validity == Validity::NO)
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;
    }
    else
    {
        cout << "You removed your credit card before it "
             << "was validated. No sale." << endl;
    }

    card_inserted = false;
    card_validity = Validity::UNKNOWN;
    return states.READY_state;
}
