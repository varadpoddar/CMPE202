#include <iostream>
#include <iomanip>
#include "Hall.h"

void Hall::print_win_count() const
{
    cout << setw(12) << name << " won "
         << win_count << " game(s)" << endl;
}
