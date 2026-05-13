#include <iostream>
#include "Enums.h"
#include "TicketMachine.h"

using namespace std;

void TicketMachine::insert_credit_card()  // Action 1
{
    switch (state)
    {
        case State::READY:
        {
            if (!card_inserted)
            {
                cout << "Validating your credit card. " << endl;

                card_inserted = true;
                card_validity = Validity::UNKNOWN;
                state = State::VALIDATING;
            }
            else if (card_validity == Validity::NO)
            {
                cout << "*** Credit card rejected. *** " << endl;
                cout << "Remove your card." << endl;
            }
            else
            {
                cout << "Remove the credit card that's "
                     << "already inserted." << endl;
            }

            break;
        }

        case State::VALIDATING:
        {
            if (card_validity == Validity::NO)
            {
                cout << "*** Credit card rejected. *** " << endl;
                cout << "Remove your card." << endl;
                state = State::READY;
            }
            else
            {
                cout << "You've already inserted your credit card. "
                     << "Checking its validation." << endl;
            }

            break;
        }

        case State::TICKET_SOLD:
        {
            cout << "Take the ticket you've already bought."
                 << endl;

            card_inserted = true;
            card_validity = Validity::UNKNOWN;
            break;
        }

        case State::SOLD_OUT:
        {
            cout << "*** Game sold out. ***" << endl;
            cout << "Remove your credit card." << endl;

            card_inserted = true;
            card_validity = Validity::UNKNOWN;

            break;
        }
    }
}

void TicketMachine::check_validity()  // Action 2
{
    switch (state)
    {
        case State::READY:
        {
            if (!card_inserted)
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

            break;
        }

        case State::VALIDATING:
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

                state = State::TICKET_SOLD;
            }
            else
            {
                cout << "*** Credit card rejected. *** " << endl;
                cout << "Remove your card." << endl;

                state = State::READY;
            }

            break;
        }

        case State::TICKET_SOLD:
        {
            cout << "Take the ticket that you've already bought. "
                 << endl;
            break;
        }

        case State::SOLD_OUT:
        {
            cout << "*** Game sold out. ***" << endl;

            if (card_inserted)
            {
                cout << "Remove your credit card." << endl;
            }

            break;
        }
    }
}

void TicketMachine::take_ticket()  // Action 3
{
    switch (state)
    {
        case State::READY:
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

            break;
        }

        case State::VALIDATING:
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

            break;
        }

        case State::TICKET_SOLD:
        {
            cout << "Remove your credit card. "
                 << "Enjoy the game!" << endl;

            count--;

            if (count > 0)
            {
                state = State::READY;
            }
            else
            {
                state = State::SOLD_OUT;
            }

            break;
        }

        case State::SOLD_OUT:
        {
            cout << "*** Game sold out. ***" << endl;

            if (card_inserted)
            {
                cout << "Remove your credit card." << endl;
            }

            break;
        }
    }
}

void TicketMachine::remove_credit_card()  // Action 4
{
    switch (state)
    {
        case State::READY:
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
            break;
        }

        case State::VALIDATING:
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
            state = State::READY;
            break;
        }

        case State::TICKET_SOLD:
        {
            cout << "First take your ticket." << endl;
            break;
        }

        case State::SOLD_OUT:
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

            break;
        }
    }
}

void TicketMachine::run()
{
    int command;

    do
    {
        cout << endl;
        cout << "1: insert card, 2: check card validity" << endl;
        cout << "3: take ticket, 4: remove card, 0: quit" << endl;
        cout << "[" << state << " " << count
             << " " << boolalpha << card_inserted
             << " " << card_validity << "] ";
        cout << "Command? ";

        cin >> command;

        switch (command)
        {
            case 1: insert_credit_card(); break;
            case 2: check_validity();     break;
            case 3: take_ticket();        break;
            case 4: remove_credit_card(); break;

            case 0: cout << endl << "Done!" << endl; break;

            default: cout << "*** Invalid command. ***" << endl;
        }

    } while (command != 0);
}
