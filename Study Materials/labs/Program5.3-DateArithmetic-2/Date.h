#ifndef DATE_H_
#define DATE_H_

#include <set>

using namespace std;

class Date
{
public:
    Date(const int year, const int month, const int day)
        : julian(to_julian(year, month, day)) {}

    int get_year()  const;
    int get_month() const;
    int get_day()   const;

    Date add_days(const int n) const;
    int days_from(const Date& other) const;

    friend ostream& operator<<(ostream& ostr, const Date& date);

private:
    static const set<int> LONG_MONTHS;

    static const int JANUARY  = 1;
    static const int FEBRUARY = 2;
    static const int DECEMBER = 12;

    static const long GREGORIAN_START_YEAR  = 1582;
    static const long GREGORIAN_START_MONTH = 10;
    static const long GREGORIAN_START_DATE  = 15;

    static const int MAX_MONTH_DAYS  = 31;
    static const int MONTHS_PER_YEAR = 12;

    Date(int j) : julian(j) {}

    int julian;

    static int days_in_month(const int year, const int month);
    static bool is_leap_year(const int year);

    static int to_julian(const int year, const int month,
                         const int day);
    static void to_ymd(const int julian, int& year, int& month,
                                         int& day);
};

#endif /* DATE_H_ */
