#ifndef ENUMS_H_
#define ENUMS_H_

#include <iostream>

using namespace std;

enum class SportType { BASEBALL, FOOTBALL, VOLLEYBALL };

inline ostream& operator <<(ostream& ostr, const SportType& type)
{
    switch (type)
    {
        case SportType::BASEBALL   : ostr << "baseball";   break;
        case SportType::FOOTBALL   : ostr << "football";   break;
        case SportType::VOLLEYBALL : ostr << "volleyball"; break;
    }

    return ostr;
}

enum class Weekend { SATURDAY, SUNDAY };

inline ostream& operator <<(ostream& ostr, const Weekend& day)
{
    switch (day)
    {
        case Weekend::SATURDAY : ostr << "Saturday"; break;
        case Weekend::SUNDAY   : ostr << "Sunday";   break;
    }

    return ostr;
}
enum class HallName { NORTH, SOUTH, EAST, WEST };

inline ostream& operator <<(ostream& ostr, const HallName& hall)
{
    switch (hall)
    {
        case HallName::NORTH : ostr << "North Hall"; break;
        case HallName::SOUTH : ostr << "South Hall"; break;
        case HallName::EAST  : ostr << "East Hall";  break;
        case HallName::WEST  : ostr << "West Hall";  break;
    }

    return ostr;
}

#endif /* ENUMS_H_ */
