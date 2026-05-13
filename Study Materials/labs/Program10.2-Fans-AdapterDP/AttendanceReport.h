#ifndef ATTENDANCEREPORT_H_
#define ATTENDANCEREPORT_H_

#include <iostream>
#include <string>
#include "AttendanceData.h"

using namespace std;

class AttendanceReport
{
public:
    void print(const AttendanceData& data,
               const string title) const;

private:
    // Legacy: Cannot change!
    void legacy_print(const AttendanceData& data) const;
};

#endif /* ATTENDANCEREPORT_H_ */
