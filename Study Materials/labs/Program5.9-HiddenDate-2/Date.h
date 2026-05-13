#ifndef DATE_H_
#define DATE_H_

#include <set>

using namespace std;

class Date
{
public:
    Date() : year(2000), month(1), day(1), julian(0),
             ymd_valid(false), julian_valid(false) {}

    Date(int y, int m, int d)
        : year(y), month(m), day(d), julian(0),
          ymd_valid(true), julian_valid(false) {}

    Date(int j)
        : year(2000), month(1), day(1), julian(j),
          ymd_valid(false), julian_valid(true) {}

    int get_year();
    int get_month();
    int get_day();
    int get_julian();

    void set_julian(const int j);

    Date add_days(int n);
    int days_from(Date& other);

    void print();

private:
    static const set<int> LONG_MONTHS;

    static const int JANUARY  = 1;
    static const int FEBRUARY = 2;
    static const int DECEMBER = 12;

    static const int MAX_MONTH_DAYS  = 31;
    static const int MONTHS_PER_YEAR = 12;

    static const long GREGORIAN_START_YEAR  = 1582;
    static const long GREGORIAN_START_MONTH = 10;
    static const long GREGORIAN_START_DATE  = 15;

    int year, month, day;
    int julian;

    bool ymd_valid;
    bool julian_valid;

    static int days_in_month(const int year, const int month);
    static bool is_leap_year(const int year);

    void validate_ymd();
    void validate_julian();

    static int to_julian(const int year, const int month,
                         const int day);
    static void to_ymd(const int julian, int& year, int& month,
                                         int& day);
};

#endif /* DAY_H_ */
