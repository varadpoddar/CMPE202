#ifndef SPORTS_H_
#define SPORTS_H_

#include "Sport.h"
#include "ProvisionsFactory.h"

using namespace std;

class VarsityBaseball : public Sport
{
public:
    VarsityBaseball(ProvisionsFactory& factory)
        : Sport(Type::BASEBALL, Category::VARSITY,
                factory.make_players(get_type()),
                factory.make_venue()) {}
};

class VarsityFootball : public Sport
{
public:
    VarsityFootball(ProvisionsFactory& factory)
        : Sport(Type::FOOTBALL, Category::VARSITY,
                factory.make_players(get_type()),
                factory.make_venue()) {}
};

class IntramuralBaseball : public Sport
{
public:
    IntramuralBaseball(ProvisionsFactory& factory)
        : Sport(Type::BASEBALL, Category::INTRAMURAL,
                factory.make_players(get_type()),
                factory.make_venue()) {}
};

class IntramuralFootball : public Sport
{
public:
    IntramuralFootball(ProvisionsFactory& factory)
        : Sport(Type::FOOTBALL, Category::INTRAMURAL,
                factory.make_players(get_type()),
                factory.make_venue()) {}
};

class IntramuralVolleyball : public Sport
{
public:
    IntramuralVolleyball(ProvisionsFactory& factory)
        : Sport(Type::VOLLEYBALL,Category::INTRAMURAL,
                factory.make_players(get_type()),
                factory.make_venue()) {}
};

#endif /* SPORTS_H_ */
