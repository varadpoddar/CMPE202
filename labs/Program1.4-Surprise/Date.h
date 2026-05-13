#ifndef DATE_H_
#define DATE_H_

#include <string>

using namespace std;

class Date
{
public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    string date_string() const
    {
        return MONTH_NAMES[month] + " "  + to_string(day)
                                  + ", " + to_string(year);
    }

private:
    const string MONTH_NAMES[12] =
    {
        "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
    };

    int year, month, day;
};

#endif /* DATE_H_ */
