#ifndef SPORTDATA_H_
#define SPORTDATA_H_

#include "Enums.h"

class AttendanceData
{
public:
    virtual ~AttendanceData() {}

    virtual Venue get_venue()      const = 0;
    virtual int   get_attendance() const = 0;
};

#endif /* SPORTDATA_H_ */
