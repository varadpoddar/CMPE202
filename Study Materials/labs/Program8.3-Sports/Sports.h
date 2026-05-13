#ifndef SPORTS_H_
#define SPORTS_H_

#include <string>
#include "Sport.h"

using namespace std;

class Baseball : public Sport
{
public:
    Baseball() : Sport(Type::BASEBALL) {}

    string recruit_players() const override
    {
        return "baseball players";
    }

    string reserve_venue() const override { return "stadium"; }
};

class Football : public Sport
{
public:
    Football() : Sport(Type::FOOTBALL) {}

    string recruit_players() const override
    {
        return "football players";
    }

    string reserve_venue() const override { return "stadium"; }
};

class Volleyball : public Sport
{
public:
    Volleyball() : Sport(Type::VOLLEYBALL) {}

    string recruit_players() const override
    {
        return "volleyball players";
    }

    string reserve_venue() const override { return "open field";}
};

#endif /* SPORTS_H_ */
