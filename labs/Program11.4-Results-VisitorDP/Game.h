#ifndef GAME_H_
#define GAME_H_

#include "Node.h"
#include "Hall.h"
#include "Visitor.h"

class Game : public Node
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

    void accept(Visitor& visitor) override
    {
        visitor.visit_Game(this);
    }

    Hall *get_winner() const { return winner; }
    Hall *get_loser()  const { return loser;  }

    int get_winner_points() const { return winner_points; }
    int get_loser_points()  const { return  loser_points; }

private:
    Hall *winner;
    Hall *loser;

    int winner_points;
    int loser_points;
};

#endif /* GAME_H_ */
