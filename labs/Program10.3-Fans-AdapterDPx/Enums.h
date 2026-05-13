#ifndef ENUMS_H_
#define ENUMS_H_

#include <iostream>

using namespace std;

enum class Venue { STADIUM, FIELD };

inline ostream& operator <<(ostream& ostr, const Venue& venue)
{
    switch (venue)
    {
        case Venue::STADIUM: ostr << "stadium";    break;
        case Venue::FIELD:   ostr << "open field"; break;
    }

    return ostr;
}

#endif /* ENUMS_H_ */
