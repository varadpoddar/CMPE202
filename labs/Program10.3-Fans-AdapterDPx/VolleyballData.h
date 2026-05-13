#ifndef VOLLEYBALLDATA_H_
#define VOLLEYBALLDATA_H_

#include "AttendanceData.h"
#include "VolleyballStats.h"

class VolleyballData : public AttendanceData,
                       public VolleyballStats
{
public:
    Venue get_venue() const override
    {
        return get_stats().venue;
    }

    int get_attendance() const override
    {
        return get_stats().attendance;
    }
};

#endif /* VOLLEYBALLDATA_H_ */
