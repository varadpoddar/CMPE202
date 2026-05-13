#include <iostream>
#include "Enums.h"
#include "State.h"

using namespace std;

State *SOLD_OUT::insert_credit_card()  // Action 1
{
    cout << "*** Game sold out. ***" << endl;
    cout << "Remove your credit card." << endl;

    card_inserted = true;
    card_validity = Validity::UNKNOWN;
    return this;
}

State *SOLD_OUT::check_validity()  // Action 2
{
    cout << "*** Game sold out. ***" << endl;

    if (card_inserted)
    {
        cout << "Remove your credit card." << endl;
    }

    return this;
}

State *SOLD_OUT::take_ticket()  // Action 3
{
    cout << "*** Game sold out. ***" << endl;

    if (card_inserted)
    {
        cout << "Remove your credit card." << endl;
    }

    return this;
}

State *SOLD_OUT::remove_credit_card()  // Action 4
{
    if (card_inserted)
    {
        cout << "You've removed your credit card." << endl;

        card_inserted = false;
        card_validity = Validity::UNKNOWN;
    }
    else
    {
        cout << "No credit card inserted." << endl;
    }

    return this;
}
