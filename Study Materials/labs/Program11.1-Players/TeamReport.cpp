#include <vector>
#include <map>
#include <iostream>
#include "Player.h"
#include "Team.h"
#include "TeamReport.h"

using namespace std;

void TeamReport::print(Team_1& team) const
{
    cout << endl;
    cout << team.get_id() << endl;

    Player **players = team.get_players();

    // Iterate over an array.
    for (int i = 0; i < 9; i++)
    {
        cout << players[i]->get_student_id() << " ";
        cout << players[i]->get_last_name()  << ", ";
        cout << players[i]->get_first_name() << endl;
    }
}

void TeamReport::print(Team_2& team) const
{
    cout << endl;
    cout << team.get_id() << endl;

    // Iterate over a vector.
    for (Player *player : team.get_players())
    {
        cout << player->get_student_id() << " ";
        cout << player->get_last_name()  << ", ";
        cout << player->get_first_name() << endl;
    }
}

void TeamReport::print(Team_3& team) const
{
    cout << endl;
    cout << team.get_id() << endl;

    map<long, Player *> players = team.get_players();
    map<long, Player *>::iterator it;

    // Iterate over a map.
    for (it = players.begin(); it != players.end(); it++)
    {
        cout << it->second->get_student_id() << " ";
        cout << it->second->get_last_name()  << ", ";
        cout << it->second->get_first_name() << endl;
    }
}
