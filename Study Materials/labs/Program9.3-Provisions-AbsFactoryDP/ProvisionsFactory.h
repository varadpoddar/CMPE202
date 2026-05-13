#ifndef PROVISIONSFACTORY_H_
#define PROVISIONSFACTORY_H_

#include "Sport.h"
#include "PlayerStrategy.h"
#include "VenueStrategy.h"

using namespace std;

class ProvisionsFactory
{
public:
    virtual ~ProvisionsFactory() {}

    virtual PlayerStrategy *make_players(const Type& type) = 0;
    virtual VenueStrategy  *make_venue() = 0;
};

class VarsityFactory : public ProvisionsFactory
{
public:
    PlayerStrategy *make_players(const Type& type) override
    {
        switch (type)
        {
            case Type::BASEBALL:
                return new VarsityBaseballPlayers();
            case Type::FOOTBALL:
                return new VarsityFootballPlayers();
            case Type::VOLLEYBALL:
                return nullptr;

            default: return nullptr;
        }
    }

    VenueStrategy *make_venue() override
    {
        return new Stadium();
    }
};

class IntramuralFactory : public ProvisionsFactory
{
public:
    PlayerStrategy *make_players(const Type& type) override
    {
        switch (type)
        {
            case Type::BASEBALL:
                return new IntramuralBaseballPlayers();
            case Type::FOOTBALL:
                return new IntramuralFootballPlayers();
            case Type::VOLLEYBALL:
                return new IntramuralVolleyballPlayers();

            default: return nullptr;
        }
    }

    VenueStrategy *make_venue() override
    {
        return new OpenField();
    }
};

#endif /* PROVISIONSFACTORY_H_ */
