#include <iostream>
#include <cstdlib>

#include "Date.h"

using namespace std;

Date::Date() : year(0), month(0), day(0)
{
    cout << "*** Default constructor called for " << *this << endl;
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d)
{
    cout << "*** Constructor called for " << *this << endl;
}

Date::~Date()
{
    cout << "*** Destructor called for " << *this << endl;
}

ostream& operator <<(ostream& outs, const Date& d)
{
    outs << d.month << "/" << d.day << "/" << d.year;
    return outs;
}
