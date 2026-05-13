#include "Team.h"
#include "TeamReport.h"

int main()
{
    TeamReport printer;

    Team_1 team_1;
    printer.print(team_1);

    Team_2 team_2;
    printer.print(team_2);

    Team_3 team_3;
    printer.print(team_3);

    return 0;
}
