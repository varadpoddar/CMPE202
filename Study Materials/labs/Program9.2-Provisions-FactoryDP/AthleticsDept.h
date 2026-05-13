#ifndef ATHLETICSDEPT_H_
#define ATHLETICSDEPT_H_

#include "Sport.h"

using namespace std;

class AthleticsDept
{
public:
    AthleticsDept() : sport(nullptr) {}
    virtual ~AthleticsDept() { delete sport; }

    void generate_report(const Type& type);

private:
    Sport *sport;

    virtual Sport *create_sport(const Type& type) = 0;
};

class VarsityDept : public AthleticsDept
{
private:
    Sport *create_sport(const Type& type) override;
};

class IntramuralDept : public AthleticsDept
{
private:
    Sport *create_sport(const Type& type) override;
};

#endif /* ATHLETICSDEPT_H_ */
