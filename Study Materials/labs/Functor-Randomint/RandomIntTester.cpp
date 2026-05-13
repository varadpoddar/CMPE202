#include <iostream>
#include "RandomInt.h"

int main()
{
    RandomInt ri(5, 12);

    for (int i = 0; i < 10; i++) cout << ri() << endl;
    return 0;
}
