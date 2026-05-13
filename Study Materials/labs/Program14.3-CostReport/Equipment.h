#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include "ProvisionItem.h"
#include "ProvisionGroup.h"

using namespace std;

class Ball : public ProvisionItem
{
public:
    Ball(const double cost) : ProvisionItem("ball", cost) {}
};

class Bat : public ProvisionItem
{
public:
    Bat(const double cost) : ProvisionItem("bat", cost) {}
};

class Glove : public ProvisionItem
{
public:
    Glove(const double cost) : ProvisionItem("glove", cost) {}
};

class Equipment : public ProvisionGroup
{
public:
    Equipment() : ProvisionGroup("EQUIPMENT")
    {
        add(new Ball(5));
        add(new Bat(25));
        add(new Glove(35));
    }
};

#endif /* EQUIPMENT_H_ */
