#include <iostream>
#include <string>
#include "AttendanceData.h"
#include "BaseballData.h"
#include "FootballInfo.h"
#include "VolleyballStats.h"
#include "AttendanceReport.h"

using namespace std;

void AttendanceReport::print(const AttendanceData& data,
                             const string title) const
{
    cout << title << endl;
    legacy_print(data);
}

void AttendanceReport::print(const FootballInfo& info,
                             const string title) const
{
    Venue venue      = info.get_info().first;
    int   attendance = info.get_info().second;

    cout << title << endl;
    legacy_print(ConvertedData(venue, attendance));
}

void AttendanceReport::print(const VolleyballStats& stats,
                             const string title) const
{
    Venue venue      = stats.get_stats().venue;
    int   attendance = stats.get_stats().attendance;

    cout << title << endl;
    legacy_print(ConvertedData(venue, attendance));
}

// Legacy: Cannot change!
void AttendanceReport::legacy_print(const AttendanceData& data) const
{
    cout << "  " << data.get_venue()
         << ": " << data.get_attendance() << endl;
}
