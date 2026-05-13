#include <iostream>
#include <iomanip>
#include "Enums.h"
#include "Intramural.h"
#include "Sport.h"
#include "Game.h"

using namespace std;

void ActivitiesReportVisitor::visit_Intramural(Intramural *intramural)
{
    cout << endl << "ACTIVITIES REPORT" << endl << endl;
}

void ActivitiesReportVisitor::visit_Sport(Sport *sport)
{
    cout << setw(12) << sport->get_type() << ": "
         << sport->get_games_count() << " game(s)" << endl;
}

void ActivitiesReportVisitor::visit_Game(Game *game)
{
    // do nothing
}

void ActivitiesReportVisitor::visit_Hall(Hall *hall)
{
    // do nothing
}
