#ifndef SPORT_H_
#define SPORT_H_

#include <vector>
#include "Node.h"
#include "Game.h"
#include "Visitor.h"

using namespace std;

class Sport : public Node
{
public:
    Sport(const SportType type) : type(type) {}
    ~Sport() { for (Game *game : games) delete game; }

    void accept(Visitor& visitor) override
    {
        visitor.visit_Sport(this);

        for (Game *game : games) game->accept(visitor);
    }

    SportType get_type() const { return type; }

    void add_game(Game *game) { games.push_back(game); }
    int get_games_count() const { return games.size(); }

private:
    SportType type;
    vector<Game *> games;
};

#endif /* SPORT_H_ */
