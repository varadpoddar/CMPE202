#ifndef TEAMREPORT_H_
#define TEAMREPORT_H_

#include "Team.h"

using namespace std;

class TeamReport
{
public:
    void print(Team_1& team) const;
    void print(Team_2& team) const;
    void print(Team_3& team) const;
};

#endif /* TEAMREPORT_H_ */
