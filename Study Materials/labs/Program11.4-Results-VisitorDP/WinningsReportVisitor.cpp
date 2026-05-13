#include <iostream>
#include <iomanip>
#include "Enums.h"
#include "Intramural.h"
#include "Sport.h"
#include "Game.h"

using namespace std;

void WinningsReportVisitor::visit_Intramural(Intramural *intramural)
{
    cout << endl << "WINNINGS REPORT" << endl << endl;
}

void WinningsReportVisitor::visit_Sport(Sport *sport)
{
    // do nothing
}

void WinningsReportVisitor::visit_Game(Game *game)
{
    // do nothing
}

void WinningsReportVisitor::visit_Hall(Hall *hall)
{
    cout << setw(12) << hall->get_name() << " won "
         << hall->get_win_count() << " game(s)" << endl;
}
