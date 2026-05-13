#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "ProvisionItem.h"
#include "ProvisionGroup.h"

using namespace std;

class Cap : public ProvisionItem
{
public:
    Cap(const double cost) : ProvisionItem("cap", cost) {}
};

class Jersey : public ProvisionItem
{
public:
    Jersey(const double cost) : ProvisionItem("jersey", cost) {}
};

class Pants : public ProvisionItem
{
public:
    Pants(const double cost) : ProvisionItem("pants", cost) {}
};

class Uniform : public ProvisionGroup
{
public:
    Uniform() : ProvisionGroup("UNIFORM")
    {
        add(new Cap(15));
        add(new Jersey(25));
        add(new Pants(35));
    }
};

#endif /* UNIFORM_H_ */
