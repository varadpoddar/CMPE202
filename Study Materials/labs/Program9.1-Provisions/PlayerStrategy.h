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

class VarsityBaseballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "varsity baseball players";
    }
};

class VarsityFootballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "varsity football players";
    }
};

class IntramuralBaseballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "intramural baseball players";
    }
};

class IntramuralFootballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "intramural football players";
    }
};

class IntramuralVolleyballPlayers : public PlayerStrategy
{
public:
    string strategy() const override
    {
        return "intramural volleyball players";
    }
};

#endif /* PLAYERSTRATEGY_H_ */
