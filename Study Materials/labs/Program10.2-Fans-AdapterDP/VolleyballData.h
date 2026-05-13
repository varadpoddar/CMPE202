#ifndef VOLLEYBALLDATA_H_
#define VOLLEYBALLDATA_H_

#include "AttendanceData.h"
#include "VolleyballStats.h"

class VolleyballData : public AttendanceData
{
public:
    VolleyballData(VolleyballStats stats)
        : volleyball_stats(stats) {}

    Venue get_venue() const override
    {
        return volleyball_stats.get_stats().venue;
    }

    int get_attendance() const override
    {
        return volleyball_stats.get_stats().attendance;
    }

private:
    VolleyballStats volleyball_stats;
};

#endif /* VOLLEYBALLDATA_H_ */
