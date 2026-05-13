#ifndef STATESBLOCK_H_
#define STATESBLOCK_H_

#include "State.h"

class StatesBlock
{
public:
    StatesBlock(int& count, bool& card_inserted,
                Validity& card_validity)
    {
        READY_state = new READY(*this, count,
                                card_inserted,
                                card_validity);
        VALIDATING_state = new VALIDATING(*this, count,
                                          card_inserted,
                                          card_validity);
        TICKET_SOLD_state = new TICKET_SOLD(*this, count,
                                            card_inserted,
                                            card_validity);
        SOLD_OUT_state = new SOLD_OUT(*this, count,
                                      card_inserted,
                                      card_validity);
    }

    ~StatesBlock()
    {
        delete READY_state;
        delete VALIDATING_state;
        delete TICKET_SOLD_state;
        delete SOLD_OUT_state;
    }

    State *get_initial_state() const { return READY_state; }

    friend READY;
    friend VALIDATING;
    friend TICKET_SOLD;
    friend SOLD_OUT;

private:
    READY       *READY_state;
    VALIDATING  *VALIDATING_state;
    TICKET_SOLD *TICKET_SOLD_state;
    SOLD_OUT    *SOLD_OUT_state;
};

#endif /* STATESBLOCK_H_ */
