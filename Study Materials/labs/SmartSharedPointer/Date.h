#ifndef DATE_H_
#define DATE_H_

#include <iostream>

using namespace std;

class Date
{
public:
    // Constructors
    Date();
    Date(int y, int m, int d);

    // Destructor
    ~Date();

    void set_year(int y)  { year = y; }

    friend ostream& operator <<(ostream& outs, const Date& d);

private:
    int year, month, day;
};

#endif
