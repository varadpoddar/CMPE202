#include "BaseballReporter.h"
#include "LogReport.h"
#include "GraphReport.h"
#include "TableReport.h"
#include "FanClubReport.h"

using namespace std;

int main()
{
    BaseballReporter *reporter = new BaseballReporter();

    new LogReport(reporter);
    new GraphReport(reporter);
    new TableReport(reporter);

    FanClubReport *fan_club = new FanClubReport(reporter, "George");

    reporter->distribute_content();

    fan_club->print_report();
}
