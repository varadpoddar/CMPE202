#ifndef REGION_H_
#define REGION_H_

#include <iostream>

using namespace std;

enum class Region
{
    CHINA, FRANCE, INDIA, ITALY, MEXICO, PERSIA, US
};

inline ostream& operator <<(ostream& ostr, const Region& region)
{
    switch (region)
    {
        case Region::CHINA:  ostr << "China";  break;
        case Region::FRANCE: ostr << "France"; break;
        case Region::INDIA:  ostr << "India";  break;
        case Region::ITALY:  ostr << "Italy";  break;
        case Region::MEXICO: ostr << "Mexico"; break;
        case Region::PERSIA: ostr << "Persia"; break;
        case Region::US:     ostr << "US";     break;
    }

    return ostr;
}

#endif /* REGION_H_ */
