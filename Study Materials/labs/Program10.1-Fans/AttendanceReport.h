#ifndef ATTENDANCEREPORT_H_
#define ATTENDANCEREPORT_H_

#include <string>
#include "AttendanceData.h"
#include "FootballInfo.h"
#include "VolleyballStats.h"

using namespace std;

class AttendanceReport
{
public:
    void print(const AttendanceData& data,
               const string title) const;

    void print(const FootballInfo& info,
               const string title) const;

    void print(const VolleyballStats& stats,
               const string title) const;

private:
    class ConvertedData : public AttendanceData
    {
    public:
        ConvertedData(const Venue v, const int a)
            : venue(v), attendance(a) {}

        Venue get_venue()      const override { return venue; }
        int   get_attendance() const override { return attendance; }

    private:
        Venue venue;
        int   attendance;
    };

    // Legacy: Cannot change!
    void legacy_print(const AttendanceData& data) const;
};

#endif /* ATTENDANCEREPORT_H_ */
