#ifndef ENUMS_H_
#define ENUMS_H_

#include <iostream>

using namespace std;

enum class State
{
    READY, VALIDATING, TICKET_SOLD, SOLD_OUT
};

inline ostream& operator <<(ostream& ostr, const State& state)
{
    switch (state)
    {
        case State::READY:       ostr << "READY";       break;
        case State::VALIDATING:  ostr << "VALIDATING";  break;
        case State::TICKET_SOLD: ostr << "TICKET_SOLD"; break;
        case State::SOLD_OUT:    ostr << "SOLD_OUT";    break;
    }

    return ostr;
}

enum class Validity
{
    YES, NO, UNKNOWN
};

inline ostream& operator <<(ostream& ostr, const Validity& valid)
{
    switch (valid)
    {
        case Validity::YES:     ostr << "yes";     break;
        case Validity::NO:      ostr << "no";      break;
        case Validity::UNKNOWN: ostr << "unknown"; break;
    }

    return ostr;
}

#endif /* ENUMS_H_ */
