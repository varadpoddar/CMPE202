#ifndef GAME_H_
#define GAME_H_

#include "Hall.h"

using namespace std;

class Game
{
public:
    Game(Hall * const winner, const int winner_points,
         Hall * const loser , const int loser_points)
        : winner(winner), loser(loser),
          winner_points(winner_points),
          loser_points(loser_points)
    {
        winner->increment_win_count();
    }

    void print_game_score() const;

private:
    Hall *winner;
    Hall *loser;

    int winner_points;
    int loser_points;
};

#endif /* GAME_H_ */
