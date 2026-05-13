#ifndef STATE_H_
#define STATE_H_

#include <string>
#include "Enums.h"

using namespace std;

class StatesBlock;

class State
{
public:
    State(const string id, StatesBlock& sb,
          int& cnt, bool& ci, Validity& cv)
        : id(id), states(sb),
          count(cnt), card_inserted(ci), card_validity(cv) {}
    virtual ~State() {}

    string get_id() const { return id; }

    virtual State *insert_credit_card() = 0;  // Action 1
    virtual State *check_validity()     = 0;  // Action 2
    virtual State *take_ticket()        = 0;  // Action 3
    virtual State *remove_credit_card() = 0;  // Action 4

private:
    string id;

protected:
    StatesBlock& states;

    int&      count;
    bool&     card_inserted;
    Validity& card_validity;
};

class READY : public State
{
public:
    READY(StatesBlock& states, int& count,
          bool& card_inserted, Validity& card_validity)
        : State("READY", states, count,
                card_inserted, card_validity) {}

private:
    State *insert_credit_card() override;  // Action 1
    State *check_validity()     override;  // Action 2
    State *take_ticket()        override;  // Action 3
    State *remove_credit_card() override;  // Action 4
};

class VALIDATING : public State
{
public:
    VALIDATING(StatesBlock& states, int& count,
               bool& card_inserted, Validity& card_validity)
        : State("VALIDATING", states, count,
                card_inserted, card_validity) {}

private:
    State *insert_credit_card() override;  // Action 1
    State *check_validity()     override;  // Action 2
    State *take_ticket()        override;  // Action 3
    State *remove_credit_card() override;  // Action 4
};

class TICKET_SOLD : public State
{
public:
    TICKET_SOLD(StatesBlock& states, int& count,
                bool& card_inserted, Validity& card_validity)
        : State("TICKET_SOLD", states, count,
                card_inserted, card_validity) {}

private:
    State *insert_credit_card() override;  // Action 1
    State *check_validity()     override;  // Action 2
    State *take_ticket()        override;  // Action 3
    State *remove_credit_card() override;  // Action 4
};

class SOLD_OUT : public State
{
public:
    SOLD_OUT(StatesBlock& states, int& count,
             bool& card_inserted, Validity& card_validity)
        : State("SOLD_OUT", states, count,
                card_inserted, card_validity) {}

private:
    State *insert_credit_card() override;  // Action 1
    State *check_validity()     override;  // Action 2
    State *take_ticket()        override;  // Action 3
    State *remove_credit_card() override;  // Action 4
};

#endif /* STATE_H_ */
