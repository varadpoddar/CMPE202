#include <iostream>
#include <set>
#include <math.h>
#include "Date.h"

int Date::get_year()
{
    validate_ymd();
    return year;
}

int Date::get_month()
{
    validate_ymd();
    return month;
}

int Date::get_day()
{
    validate_ymd();
    return day;
}

Date Date::add_days(const int n)
{
    validate_julian();
    return Date(julian + n);
}

int Date::days_from(Date& other)
{
    validate_julian();
    other.validate_julian();
    return julian - other.julian;
}

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

void Date::validate_ymd()
{
    if (!ymd_valid)
    {
        to_ymd(julian, year, month, day);
        ymd_valid = true;
    }
}

void Date::validate_julian()
{
    if (!julian_valid)
    {
        julian = to_julian(year, month, day);
        julian_valid = true;
    }
}

int Date::to_julian(const int year, const int month, const int day)
{
    int y = year;
    if (year < 0) y++;

    int m = month;
    if (month > 2) m++;
    else
    {
        y--;
        m += 13;
    }

    long j = static_cast<long>(floor(365.25*y) + floor(30.6001*m))
                    + day + 1720995;

    const long GREGORIAN_CUTOFF =
        GREGORIAN_START_DATE +
        MAX_MONTH_DAYS*(GREGORIAN_START_MONTH +
                               MONTHS_PER_YEAR*GREGORIAN_START_YEAR);

    if (day + MAX_MONTH_DAYS*(month + MONTHS_PER_YEAR*year) >=
                                                    GREGORIAN_CUTOFF)
    {
        int x = static_cast<int>(0.01*y);
        j += 2 - x + static_cast<int>(0.25*x);
    }

    return j;
}

void Date::to_ymd(int julian, int& year, int& month, int& day)
{
    long ja = julian;

    const long GREGORIAN_CUTOFF = 2299161;

    if (julian >= GREGORIAN_CUTOFF)
    {
        long jalpha = static_cast<long>(
            (static_cast<float>(julian - 1867216) - 0.25)/36524.25);
        ja += 1 + jalpha - static_cast<long>(0.25*jalpha);
    }

    long jb = ja + 1524;
    long jc = static_cast<long>(
        6680.0 + (static_cast<float>(jb - 2439870) - 122.1)/365.25);
    long jd = static_cast<long>(365*jc + (0.25*jc));
    long je = static_cast<long>((jb - jd)/30.6001);

    day = jb - jd - static_cast<long>(30.6001*je);

    month = je - 1;
    if (month > 12) month -= 12;

    year = jc - 4715;
    if (month > 2) year--;
    if (year <= 0) year--;
}

void Date::print()
{
    validate_ymd();

    cout << month << "/" << day << "/";
    if (year > 0) cout <<  year;
    else          cout << -year << " BCE";
}
