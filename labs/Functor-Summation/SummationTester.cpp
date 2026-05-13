#include <iostream>
#include <iomanip>
#include "Summation.h"

using namespace std;

int main()
{
    Summation adder;

    for(int i = 1; i < 20; i += 2)
    {
        cout << "Add " << setw(2) << i << ": "
             << setw(3) << adder(i) << endl;

    }

    return 0;
}
