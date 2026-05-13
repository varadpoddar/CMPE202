#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>

using namespace std;

class Date
{
public:
    Date(const int y, const int m, const int d)
        : year(y), month(m), day(d) {}

    friend ostream& operator <<(ostream& ostr, const Date& date);

private:
    static const string MONTH_NAMES[13];

    int year, month, day;
};

#endif /* DATE_H_ */
