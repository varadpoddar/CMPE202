#ifndef FOOTBALLINFO_H_
#define FOOTBALLINFO_H_

#include <utility>
#include "Enums.h"

using namespace std;

class FootballInfo  // cannot change!
{
public:
    FootballInfo()
    {
        info.first  = Venue::STADIUM;
        info.second = 2000;
    }

    pair<Venue, int> get_info() const { return info; }

private:
    pair<Venue, int> info;
};

#endif /* FOOTBALLINFO_H_ */
