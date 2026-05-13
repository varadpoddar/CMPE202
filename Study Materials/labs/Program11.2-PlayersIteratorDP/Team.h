#ifndef TEAM_H_
#define TEAM_H_

#include <string>
#include <vector>
#include <map>
#include "Player.h"
#include "Iterator.h"

using namespace std;

class Team
{
public:
    Team(const string id) : id(id) {}
    virtual ~Team() {}

    string get_id() const { return id; }

    virtual Iterator *create_iterator() = 0;

private:
    string id;
};

class Team_1: public Team
{
public:
    Team_1();

    ~Team_1() { for (int i = 0; i < 9; i++) delete players[i]; }

    Iterator *create_iterator() override
    {
        return new ArrayIterator(players);
    }

private:
    Player *players[9];  // array
};

class Team_2 : public Team
{
public:
    Team_2();

    ~Team_2 () { for (int i = 0; i < 9; i++) delete players[i]; }

    Iterator *create_iterator() override
    {
        return new VectorIterator(players);
    }

private:
    vector<Player *> players;  // vector
};

class Team_3 : public Team
{
public:
    Team_3();

    ~Team_3 ()
    {
        for (auto it = players.begin(); it != players.end(); it++)
        {
            delete it->second;
        }
    }

    Iterator *create_iterator() override
    {
        return new MapIterator(players);
    }

private:
    map<long, Player *> players;  // map
};

#endif /* TEAM_H_ */
