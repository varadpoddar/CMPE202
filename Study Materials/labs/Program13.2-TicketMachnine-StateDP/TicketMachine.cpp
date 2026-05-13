#include <iostream>
#include "State.h"
#include "TicketMachine.h"

using namespace std;

void TicketMachine::run()
{
    int command;

    do
    {
        cout << endl;
        cout << "1: insert card, 2: check card validity" << endl;
        cout << "3: take ticket, 4: remove card, 0: quit" << endl;
        cout << "[" << state->get_id() << " " << count
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
