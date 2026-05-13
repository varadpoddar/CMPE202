#include <iostream>
#include "Player.h"
#include "Team.h"
#include "TeamReport.h"

using namespace std;

void TeamReport::print(Team& team) const
{
    cout << endl;
    cout << team.get_id() << endl;

    Iterator *it = team.create_iterator();

    while (it->has_next())
    {
        Player *player = it->next();
        cout << player->get_student_id() << " ";
        cout << player->get_last_name()  << ", ";
        cout << player->get_first_name() << endl;
    }

    delete it;
}
