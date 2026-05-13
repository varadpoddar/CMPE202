#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <ostream>
#include <set>

using namespace std;

class Date
{
public:
    Date(const int y, const int m, const int d)
        : year(y), month(m), day(d) {}

    int get_year()  const { return year; }
    int get_month() const { return month; }
    int get_day()   const { return day; }

    Date add_days(int n) const;
    int days_from(const Date& other) const;

    friend ostream& operator<<(ostream& ostr, const Date& date);

private:
    static const set<int> LONG_MONTHS;

    static const int JANUARY  = 1;
    static const int FEBRUARY = 2;
    static const int DECEMBER = 12;

    static const int GREGORIAN_START_YEAR = 1582;
    static const int GREGORIAN_START_MONTH = 10;
    static const int GREGORIAN_START_DATE = 15;
    static const int JULIAN_END_DATE = 4;

    int year, month, day;

    static int days_in_month(const int year, const int month);
    static bool is_leap_year(const int year);

    int compare_to(const Date& other) const;
    Date next_date() const;
    Date previous_date() const;
};

#endif /* DATE_H_ */
