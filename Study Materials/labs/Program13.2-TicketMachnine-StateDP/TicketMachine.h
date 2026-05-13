#ifndef TICKETMACHINE_H_
#define TICKETMACHINE_H_

//#include <ctime>

#include "Enums.h"
#include "State.h"
#include "StatesBlock.h"

class TicketMachine
{
public:
    TicketMachine(const int c)
        : count(c), card_inserted(false),
          card_validity(Validity::UNKNOWN)
    {
        srand(time(nullptr));

        block = new StatesBlock(count, card_inserted, card_validity);
        state = block->get_initial_state();
    }

    void run();

    ~TicketMachine() { delete block; }

private:
    int      count;
    bool     card_inserted;
    Validity card_validity;

    StatesBlock *block;
    State *state;

    void insert_credit_card()
    {
        state = state->insert_credit_card();
    }

    void check_validity()
    {
        state = state->check_validity();
    }

    void take_ticket()
    {
        state = state->take_ticket();
    }

    void remove_credit_card()
    {
        state = state->remove_credit_card();
    }
};

#endif /* TICKETMACHINE_H_ */
