#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
    Date date1(2025, 9, 2);  // September 2, 2025
    Date date2(2027, 4, 3);  // April 3, 2027

    cout << "date1 = " << date1 << endl;
    cout << "date2 = " << date2 << endl;

    int count = date2.days_from(date1);
    cout << "count = date2.days_from(date1) = " << count << endl;

    cout << "date1.add_days(count) should be date2: "
         << date1.add_days(count) << endl;

    return 0;
}
