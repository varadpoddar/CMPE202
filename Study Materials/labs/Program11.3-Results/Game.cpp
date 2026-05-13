#include <iostream>
#include <iomanip>
#include "Hall.h"
#include "Game.h"

using namespace std;

void Game::print_game_score() const
{
    cout << setw(14) << winner->get_name() << " beat "
         << setw(10) << loser->get_name()
         << setw(3)  << winner_points
         << " to "   << setw(2) << loser_points << endl;
}
