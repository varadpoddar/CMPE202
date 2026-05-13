#ifndef SPORT_H_
#define SPORT_H_

#include <iostream>
#include <string>

#include "PlayerStrategy.h"
#include "VenueStrategy.h"

using namespace std;

enum class Type { BASEBALL, FOOTBALL, VOLLEYBALL };

inline ostream& operator <<(ostream& ostr, const Type type)
{
    switch (type)
    {
        case Type::BASEBALL:   ostr << "baseball";   break;
        case Type::FOOTBALL:   ostr << "football";   break;
        case Type::VOLLEYBALL: ostr << "volleyball"; break;
    }

    return ostr;
}

enum class Category { VARSITY, INTRAMURAL };

inline ostream& operator <<(ostream& ostr, const Category category)
{
    switch (category)
    {
        case Category::VARSITY:    ostr << "varsity";    break;
        case Category::INTRAMURAL: ostr << "intramural"; break;
    }

    return ostr;
}

class Sport
{
public:
    Sport(const Type t, const Category c,
          PlayerStrategy * const ps, VenueStrategy * const vs)
        : type(t), category(c),
          player_strategy(ps), venue_strategy(vs) {}

    ~Sport()
    {
        delete player_strategy;
        delete venue_strategy;
    }

    Type     get_type()     const { return type; }
    Category get_category() const { return category; }

    string recruit_players() const
    {
        return player_strategy->strategy();
    }

    string reserve_venue() const
    {
        return venue_strategy->strategy();
    }

    void set_player_strategy(PlayerStrategy * const ps)
    {
        player_strategy = ps;
    }

    void set_venue_strategy(VenueStrategy * const vs)
    {
        venue_strategy = vs;
    }

private:
    Type type;
    Category category;
    PlayerStrategy *player_strategy;
    VenueStrategy  *venue_strategy;
};

#endif /* SPORT_H_ */
