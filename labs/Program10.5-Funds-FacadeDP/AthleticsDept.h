#ifndef ATHLETICSDEPT_H_
#define ATHLETICSDEPT_H_

#include <iostream>
#include "FundRaiser.h"

using namespace std;

class AthleticsDept
{
public:
    void raise_funds()
    {
        FundRaiser fund_raiser;

        cout << endl << "ATHLETICS DEPARTMENT" << endl;
        fund_raiser.do_fund_raising();
    }
};

#endif /* ATHLETICSDEPT_H_ */
