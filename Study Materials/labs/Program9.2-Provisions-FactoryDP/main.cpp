#include <iostream>
#include "Sport.h"
#include "Sports.h"
#include "AthleticsDept.h"

using namespace std;

int main()
{
    VarsityDept varsity;

    varsity.generate_report(Type::BASEBALL);
    varsity.generate_report(Type::FOOTBALL);

    IntramuralDept intramural;

    intramural.generate_report(Type::BASEBALL);
    intramural.generate_report(Type::FOOTBALL);
    intramural.generate_report(Type::VOLLEYBALL);

    return 0;
}