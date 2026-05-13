#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
    Date date(2023, 9, 2);  // SEP 2, 2023
    cout << date.date_string() << endl;

    return 0;
}
