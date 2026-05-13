#ifndef BASEBALLDATA_H_
#define BASEBALLDATA_H_

#include "Enums.h"
#include "AttendanceData.h"

class BaseballData : public AttendanceData
{
public:
    Venue get_venue()      const override { return Venue::STADIUM; }
    int   get_attendance() const override { return 500; }
};

#endif /* BASEBALLDATA_H_ */
