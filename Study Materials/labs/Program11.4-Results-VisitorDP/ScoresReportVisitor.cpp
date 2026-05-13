#include <iostream>
#include <iomanip>
#include "Enums.h"
#include "Intramural.h"
#include "Sport.h"
#include "Game.h"

using namespace std;

void ScoresReportVisitor::visit_Intramural(Intramural *intramural)
{
    cout << endl << "SCORES REPORT" << endl;
}

void ScoresReportVisitor::visit_Sport(Sport *sport)
{
    cout << endl << "  " << sport->get_type() << endl;
}

void ScoresReportVisitor::visit_Game(Game *game)
{
    Hall *winner = game->get_winner();
    Hall *loser  = game->get_loser();

    int winner_points = game->get_winner_points();
    int  loser_points = game->get_loser_points();

    cout << setw(14) << winner->get_name() << " beat "
         << setw(10) << loser->get_name()
         << setw(3)  << winner_points
         << " to "   << setw(2) << loser_points << endl;
}

void ScoresReportVisitor::visit_Hall(Hall *hall)
{
    // do nothing
}
