#include <iostream>
#include "Taxes.h"

using namespace std;

int main()
{
    GeneralTax *tax1 = new GeneralTax();
    cout << "General taxes owed = $"
         << tax1->amount_owed(10000.00) << endl;

    GeneralTax *tax2 = new LocalTax();
    cout << "  Local taxes owed = $"
         << tax2->amount_owed(10000.00) << endl;

    GeneralTax *tax3 = new MaxTax();
    cout << "    Max taxes owed = $"
         << tax3->amount_owed(10000.00) << endl;

    delete tax1;
    delete tax2;
    delete tax3;
}
