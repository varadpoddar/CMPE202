#ifndef SUNSCREEN_H_
#define SUNSCREEN_H_

#include "ProvisionItem.h"

using namespace std;

class Sunscreen : public ProvisionItem
{
public:
    Sunscreen(const double cost)
        : ProvisionItem("sunscreen", cost) {}
};

#endif /* SUNSCREEN_H_ */
