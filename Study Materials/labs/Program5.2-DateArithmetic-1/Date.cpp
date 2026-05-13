#include <iostream>
#include <set>
#include "Date.h"

using namespace std;

const set<int> Date::LONG_MONTHS { 1, 3, 5, 7, 8, 10, 12 };

int Date::days_in_month(const int year, const int month)
{
   if (LONG_MONTHS.find(month) != LONG_MONTHS.end()) return 31;
   if (month == 2) return is_leap_year(year) ? 29 : 28;
   return 30;
}

bool Date::is_leap_year(const int year)
{
   if (year%4 != 0) return false;
   if (year < GREGORIAN_START_YEAR) return true;

   return (year%100 != 0) || (year%400 == 0);
}

int Date::compare_to(const Date& other) const
{
    if (year > other.year)   return 1;
    if (year < other.year)   return -1;
    if (month > other.month) return 1;
    if (month < other.month) return -1;

    return day - other.day;
}

Date Date::next_date() const
{
    int y = year;
    int m = month;
    int d = day;

    if (   y == GREGORIAN_START_YEAR
        && m == GREGORIAN_START_MONTH
        && d == JULIAN_END_DATE)      d = GREGORIAN_START_DATE;
    else if (d < days_in_month(y, m)) d++;
    else
    {
        d = 1;
        m++;

        if (m > DECEMBER)
        {
            m = JANUARY;
            y++;
            if (y == 0) y++;  // no year 0
        }
    }

    return Date(y, m, d);
}

Date Date::previous_date() const
{
    int y = year;
    int m = month;
    int d = day;

    if (   y == GREGORIAN_START_YEAR
        && m == GREGORIAN_START_MONTH
        && d == GREGORIAN_START_DATE) d = JULIAN_END_DATE;
    else if (d > 1)                   d--;
    else
    {
        m--;

        if (m < JANUARY)
        {
            m = DECEMBER;
            y--;
            if (y == 0) y--;  // no year 0
        }

        d = days_in_month(y, m);
    }

    return Date(y, m, d);
}

Date Date::add_days(int n) const
{
    Date date = *this;

    while (n > 0)
    {
        date = date.next_date();
        n--;
    }

    while (n < 0)
    {
        date = date.previous_date();
        n++;
    }

    return date;
}

int Date::days_from(const Date& other) const
{
    Date date = *this;
    int n = 0;

    while (date.compare_to(other) > 0)
    {
        date = date.previous_date();
        n++;
    }

    while (date.compare_to(other) < 0)
    {
        date = date.next_date();
        n--;
    }

    return n;
}

ostream& operator<<(ostream& ostr, const Date& date)
{
    ostr << date.month << "/" << date.day << "/";

    if (date.year > 0) ostr <<  date.year;
    else               ostr << -date.year << " BCE";

    return ostr;
}
