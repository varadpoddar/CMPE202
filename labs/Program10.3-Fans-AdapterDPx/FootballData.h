#ifndef FOOTBALLDATA_H_
#define FOOTBALLDATA_H_

#include "AttendanceData.h"
#include "FootballInfo.h"

class FootballData : public AttendanceData,
                     public FootballInfo
{
public:
    Venue get_venue() const override
    {
        return get_info().first;
    }

    int get_attendance() const override
    {
        return get_info().second;
    }
};

#endif /* FOOTBALLDATA_H_ */
