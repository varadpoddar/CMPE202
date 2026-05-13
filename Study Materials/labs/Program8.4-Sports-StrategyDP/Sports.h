#ifndef SPORTS_H_
#define SPORTS_H_

#include "Sport.h"
#include "PlayerStrategy.h"
#include "VenueStrategy.h"

using namespace std;

class Baseball : public Sport
{
public:
    Baseball() : Sport(Type::BASEBALL,
                       new BaseballPlayers(),
                       new Stadium()) {}
};

class Football : public Sport
{
public:
    Football() : Sport(Type::FOOTBALL,
                       new FootballPlayers(),
                       new Stadium()) {}
};

class Volleyball : public Sport
{
public:
    Volleyball() : Sport(Type::VOLLEYBALL,
                         new VolleyballPlayers(),
                         new OpenField()) {}
};

#endif /* SPORTS_H_ */
