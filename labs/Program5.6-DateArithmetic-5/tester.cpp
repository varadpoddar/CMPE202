#include <iostream>
#include <iomanip>
#include "Date.h"

using namespace std;

int main()
{
    Date d(2030, 1, 31);  // January 31, 2030
    cout << "starting date d = "; d.print(); cout << endl;
    cout << "d.get_julian() = " << d.get_julian() << endl << endl;

    d.set_month(2);
    cout << "date after d.set_month(2): ";
    d.print(); cout << endl << endl;

    int j = d.get_julian();
    cout << "j = d.get_julian() = " << j << endl;

    d.set_julian(j);
    cout << "date after d.set_julian(j): ";
    d.print(); cout << endl;

    return 0;
}
