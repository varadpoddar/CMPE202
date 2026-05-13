#include <iostream>
#include "Enums.h"
#include "State.h"
#include "StatesBlock.h"

using namespace std;

State *READY::insert_credit_card()  // Action 1
{
    if (!card_inserted)
    {
        cout << "Validating your credit card. " << endl;

        card_inserted = true;
        card_validity = Validity::UNKNOWN;
        return states.VALIDATING_state;
    }
    else if (card_validity == Validity::NO)
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;
        return this;
    }
    else
    {
        cout << "Remove the credit card that's "
             << "already inserted." << endl;
        return this;
    }
}

State *READY::check_validity()  // Action 2
{
    if (card_inserted)
    {
        cout << "First insert your credit card." << endl;
    }
    else if (card_validity == Validity::YES)
    {
        cout << "Remove the credit card that's "
             << "already inserted." << endl;
    }
    else
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;
    }

    return this;
}

State *READY::take_ticket()  // Action 3
{
    if (!card_inserted)
    {
        cout << "First insert your credit card." << endl;
    }
    else if (card_validity == Validity::UNKNOWN)
    {
        cout << "Still checking your credit card's validity."
             << endl;
    }
    else if (card_validity == Validity::YES)
    {
        cout << "Take the ticket that you've already "
             << "bought. Remove your card." << endl;
    }
    else
    {
        cout << "*** Credit card rejected. *** " << endl;
        cout << "Remove your card." << endl;
    }

    return this;
}

State *READY::remove_credit_card()  // Action 4
{
    if (card_inserted)
    {
        cout << "You've removed your credit card." << endl;
    }
    else
    {
        cout << "No credit card inserted." << endl;
    }

    card_inserted = false;
    card_validity = Validity::UNKNOWN;
    return this;
}
