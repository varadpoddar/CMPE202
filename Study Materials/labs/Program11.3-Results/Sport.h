#ifndef SPORT_H_
#define SPORT_H_

#include <vector>
#include "Game.h"

using namespace std;

class Sport
{
public:
    Sport(const SportType type) : type(type) {}
    ~Sport() { for (Game *game : games) delete game; }

    void add_game(Game *game) { games.push_back(game); }

    void print_game_scores() const;
    void print_game_count()  const;

private:
    SportType type;
    vector<Game *> games;
};

#endif /* SPORT_H_ */
