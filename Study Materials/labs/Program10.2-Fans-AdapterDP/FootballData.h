#ifndef FOOTBALLDATA_H_
#define FOOTBALLDATA_H_

#include "AttendanceData.h"
#include "FootballInfo.h"

class FootballData : public AttendanceData
{
public:
    FootballData(FootballInfo info) : football_info(info) {}

    Venue get_venue() const override
    {
        return football_info.get_info().first;
    }

    int get_attendance() const override
    {
        return football_info.get_info().second;
    }

private:
    FootballInfo football_info;
};

#endif /* FOOTBALLDATA_H_ */
