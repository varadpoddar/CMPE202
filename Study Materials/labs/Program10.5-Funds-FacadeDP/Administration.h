#ifndef ADMINISTRATION_H_
#define ADMINISTRATION_H_

#include <iostream>
#include "FundRaiser.h"

using namespace std;

class Administration
{
public:
    void raise_funds()
    {
        FundRaiser fund_raiser;

        cout << endl << "SCHOOL ADMINISTRATION" << endl;
        fund_raiser.do_fund_raising();
    }
};

#endif /* ADMINISTRATION_H_ */
