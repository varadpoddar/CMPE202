#ifndef COSTREPORT_H_
#define COSTREPORT_H_

#include "Equipment.h"
#include "Uniform.h"
#include "Footwear.h"
#include "Sunscreen.h"

class CostReport
{
public:
    void generate(const Equipment *equipment,
                  const Uniform   *uniform,
                  const Footwear  *footwear,
                  const Sunscreen *sunscreen) const
    {
        // ================
        // Calculate totals
        // ================

        double equipment_total = 0;
        for (ProvisionItem *pi : (*equipment)())
        {
            equipment_total += pi->get_cost();
        }

        double uniform_total = 0;
        for (ProvisionItem *pi : (*uniform)())
        {
            uniform_total += pi->get_cost();
        }

        double footwear_total = 0;
        for (ProvisionItem *pi : (*footwear)())
        {
            footwear_total += pi->get_cost();
        }

        uniform_total += footwear_total;

        // ============
        // Print report
        // ============

        cout << "PROVISIONS" << endl;

        cout << "    " << equipment->get_id() << endl;
        for (ProvisionItem *pi : (*equipment)())
        {
            cout << "        " << *pi;
        }
        cout << "    " << equipment->get_id() << " total: $"
             << setw(2) << equipment_total << endl;

        cout << "    " << uniform->get_id() << endl;
        for (ProvisionItem *pi : (*uniform)())
        {
            cout << "        " <<* pi;
        }

        cout << "        " << footwear->get_id() << endl;
        for (ProvisionItem *pi : (*footwear)())
        {
            cout << "            " << *pi;
        }
        cout << "        " << footwear->get_id() << " total: $"
             << setw(2) << footwear_total << endl;

        cout << "    " << uniform->get_id() << " total: $"
             << setw(2) << uniform_total << endl;

        cout << "    " << *sunscreen;

        double provisions_total = equipment_total
                                + uniform_total
                                + sunscreen->get_cost();
        cout << "PROVISIONS total: $" << provisions_total << endl;

        cout << endl;
        cout << "GRAND TOTAL: $" << provisions_total << endl;
    }
};

#endif /* COSTREPORT_H_ */
