#ifndef COSTREPORT_H_
#define COSTREPORT_H_

#include "ProvisionGroup.h"

class CostReport
{
public:
    void generate(const ProvisionGroup& provisions) const
    {
        provisions.print();

        cout << endl;
        cout << "GRAND TOTAL: $" << provisions.get_cost() << endl;
    }

private:
    ProvisionGroup provisions;
};

#endif /* COSTREPORT_H_ */
