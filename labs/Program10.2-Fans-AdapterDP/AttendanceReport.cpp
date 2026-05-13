#include <iostream>
#include <string>
#include "AttendanceData.h"
#include "AttendanceReport.h"

void AttendanceReport::print(const AttendanceData& data,
                             const string title) const
{
    cout << title << endl;
    legacy_print(data);
}

// Legacy: Cannot change!
void AttendanceReport::legacy_print(const AttendanceData& data) const
{
    cout << "  " << data.get_venue()
         << ": " << data.get_attendance() << endl;
}
