#ifndef SPORTS_H_
#define SPORTS_H_

#include "Sport.h"
#include "PlayerStrategy.h"
#include "VenueStrategy.h"

using namespace std;

class VarsityBaseball : public Sport
{
public:
    VarsityBaseball() : Sport(Type::BASEBALL, Category::VARSITY,
                              new VarsityBaseballPlayers(),
                              new Stadium()) {}
};

class VarsityFootball : public Sport
{
public:
    VarsityFootball() : Sport(Type::FOOTBALL, Category::VARSITY,
                              new VarsityFootballPlayers(),
                              new Stadium()) {}
};

class IntramuralBaseball : public Sport
{
public:
    IntramuralBaseball() : Sport(Type::BASEBALL,
                                 Category::INTRAMURAL,
                                 new IntramuralBaseballPlayers(),
                                 new OpenField()) {}
};

class IntramuralFootball : public Sport
{
public:
    IntramuralFootball() : Sport(Type::FOOTBALL,
                                 Category::INTRAMURAL,
                                 new IntramuralFootballPlayers(),
                                 new OpenField()) {}
};

class IntramuralVolleyball : public Sport
{
public:
    IntramuralVolleyball() : Sport(Type::VOLLEYBALL,
                                   Category::INTRAMURAL,
                                   new IntramuralVolleyballPlayers(),
                                   new OpenField()) {}
};

#endif /* SPORTS_H_ */
