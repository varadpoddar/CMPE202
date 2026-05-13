#ifndef VOLLEYBALLSTATS_H_
#define VOLLEYBALLSTATS_H_

#include "Enums.h"

typedef struct
{
    Venue venue;
    int   attendance;
} VolleyballStruct;

class VolleyballStats  // cannot change!
{
public:
    VolleyballStats()
    {
        stats.venue      = Venue::FIELD;
        stats.attendance = 150;
    }

    VolleyballStruct get_stats() const { return stats; }

private:
    VolleyballStruct stats;
};

#endif /* VOLLEYBALLSTATS_H_ */
