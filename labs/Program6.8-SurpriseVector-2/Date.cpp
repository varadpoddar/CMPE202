#include <iostream>
#include "Date.h"

const string Date::MONTH_NAMES[13] =
{
    "",
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

ostream& operator <<(ostream& ostr, const Date& date)
{
    ostr << date.MONTH_NAMES[date.month]
         << " " << date.day << ", " << date.year;

    return ostr;
}
