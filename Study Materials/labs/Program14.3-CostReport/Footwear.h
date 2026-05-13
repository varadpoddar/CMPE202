#ifndef FOOTWEAR_H_
#define FOOTWEAR_H_

#include "ProvisionItem.h"
#include "ProvisionGroup.h"

using namespace std;

class Socks : public ProvisionItem
{
public:
    Socks(const double cost) : ProvisionItem("socks", cost) {}
};

class Shoes : public ProvisionItem
{
public:
    Shoes(const double cost) : ProvisionItem("shoes", cost) {}
};

class Footwear : public ProvisionGroup
{
public:
    Footwear() : ProvisionGroup("FOOTWEAR")
    {
        add(new Socks(5));
        add(new Shoes(50));

    }
};

#endif /* FOOTWEAR_H_ */
