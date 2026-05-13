#ifndef TICKETMACHINE_H_
#define TICKETMACHINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Enums.h"

class TicketMachine
{
public:
    TicketMachine(const int c)
        : count(c), card_inserted(false),
          card_validity(Validity::UNKNOWN), state(State::READY)
    {
        srand(time(NULL));
    }

    int      get_count()    const { return count; }
    bool     get_inserted() const { return card_inserted; }
    Validity get_validity() const { return card_validity; }
    State    get_state()    const { return state; }

    void run();

    void insert_credit_card();  // 1
    void check_validity();      // 2
    void take_ticket();         // 3
    void remove_credit_card();  // 4

private:
    int      count;
    bool     card_inserted;
    Validity card_validity;
    State    state;
};

#endif /* TICKETMACHINE_H_ */
