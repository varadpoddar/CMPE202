#include "CostReport.h"

int main()
{
    CostReport report;
    report.generate(new Equipment(), new Uniform(),
                    new Footwear(), new Sunscreen(5));

    return 0;
}
