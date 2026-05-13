#include "Team.h"
#include "TeamReport.h"

int main()
{
    TeamReport reporter;

    Team_1 team_1;
    reporter.print(team_1);

    Team_2 team_2;
    reporter.print(team_2);

    Team_3 team_3;
    reporter.print(team_3);

    return 0;
}
