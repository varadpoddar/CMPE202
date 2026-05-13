#include "Equipment.h"
#include "Uniform.h"
#include "Sunscreen.h"
#include "CostReport.h"

int main()
{
    ProvisionGroup provisions;

    provisions.add(new Equipment());
    provisions.add(new Uniform());
    provisions.add(new Sunscreen(5));

    CostReport report;
    report.generate(provisions);

    return 0;
}
