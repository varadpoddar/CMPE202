#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>

using namespace std;

class Date
{
public:
    Date() : year(2000), month(1), day(1)
    {
        cout << "(default constructor) " << endl;
    }

    Date(const int y, const int m, const int d)
        : year(y), month(m), day(d)
    {
        cout << "(regular constructor) " << *this << endl;
    }

    Date(const Date& other)
    {
        cout << "(copy constructor) " << other << endl;

        year  = other.year;
        month = other.month;
        day   = other.day;
    }

    Date& operator =(const Date& other)
    {
        cout << "(assignment operator) " << other << endl;

        if (this == &other) return *this;

        year  = other.year;
        month = other.month;
        day   = other.day;

        return *this;
    }

    ~Date()
    {
        cout << "(destructor) " << *this << endl;
    }

    friend ostream& operator <<(ostream& ostr, const Date& date);

private:
    static const string MONTH_NAMES[13];

    int year, month, day;
};

#endif /* DATE_H_ */
