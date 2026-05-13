#include <iostream>
#include <iomanip>
#include "Sport.h"
#include "Hall.h"
#include "Intramural.h"

void Intramural::print_scores_report() const
{
    cout << endl << "SCORES REPORT" << endl;

    for (Sport *sport : sports) sport->print_game_scores();
}

void Intramural::print_activities_report() const
{
    cout << endl << "ACTIVITIES REPORT" << endl << endl;

    for (Sport *sport : sports) sport->print_game_count();
}

void Intramural::print_winnings_report() const
{
    cout << endl << "WINNINGS REPORT" << endl << endl;

    for (Hall *hall : halls) hall->print_win_count();
}
