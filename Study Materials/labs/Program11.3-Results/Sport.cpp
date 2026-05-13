#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Sport.h"

using namespace std;

void Sport::print_game_scores() const
{
    cout << endl << "  " << type << endl;

    for (Game *game : games) game->print_game_score();
}

void Sport::print_game_count() const
{
    cout << setw(12) << type << ": "
         << games.size() << " game(s)" << endl;
}
