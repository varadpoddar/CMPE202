#ifndef PLAYERSTRATEGY_H_
#define PLAYERSTRATEGY_H_

#include <string>

using namespace std;

class PlayerStrategy
{
public:
    virtual ~PlayerStrategy() {}

    virtual string strategy() const = 0;
};

class BaseballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "baseball players";
    }
};

class FootballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "football players";
    }
};

class VolleyballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "volleyball players";
    }
};

#endif /* PLAYERSTRATEGY_H_ */
