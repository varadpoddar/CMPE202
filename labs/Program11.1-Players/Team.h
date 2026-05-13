#ifndef TEAM_H_
#define TEAM_H_

#include <string>
#include <vector>
#include <map>
#include "Player.h"

using namespace std;

class Team
{
public:
    Team(const string id) : id(id) {}

    string get_id() const { return id; }

private:
    string id;
};

class Team_1 : public Team
{
public:
    Team_1();

    ~Team_1() { for (int i = 0; i < 9; i++) delete players[i]; }

    Player **get_players() { return players; }

private:
    Player *players[9];  // array
};

class Team_2 : public Team
{
public:
    Team_2();

    ~Team_2 () { for (int i = 0; i < 9; i++) delete players[i]; }

    vector<Player *> get_players() const { return players; }

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

    map<long, Player *> get_players() const { return players; }

private:
    map<long, Player *> players;  // map
};

#endif /* TEAM_H_ */
