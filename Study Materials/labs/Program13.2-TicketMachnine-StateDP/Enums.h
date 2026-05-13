#ifndef ENUMS_H_
#define ENUMS_H_

#include <iostream>

using namespace std;

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
