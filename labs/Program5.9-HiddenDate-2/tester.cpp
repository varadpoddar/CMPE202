#include <iostream>
#include "Employee.h"

using namespace std;

int main()
{
    Date *date1 = new Date(2000, 1, 10);
    Employee mary(1234567890, "Mary", date1);
    cout << mary << endl;

    int julian1 = date1->get_julian();
    date1->set_julian(julian1 + 366);
    cout << mary << endl;

    Date *date2 = mary.get_birthdate();
    int julian2 = date2->get_julian();
    date2->set_julian(julian2 + 365);
    cout << mary << endl;

    return 0;
}
