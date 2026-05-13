#include <iostream>
#include "AthleticsDept.h"

using namespace std;

int main()
{
    AthleticsDept dept;

    dept.generate_report(Category::VARSITY, Type::BASEBALL);
    dept.generate_report(Category::VARSITY, Type::FOOTBALL);

    dept.generate_report(Category::INTRAMURAL, Type::BASEBALL);
    dept.generate_report(Category::INTRAMURAL, Type::FOOTBALL);
    dept.generate_report(Category::INTRAMURAL, Type::VOLLEYBALL);

    return 0;
}
