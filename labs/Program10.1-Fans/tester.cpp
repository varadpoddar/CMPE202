#include "BaseballData.h"
#include "FootballInfo.h"
#include "VolleyballStats.h"
#include "AttendanceReport.h"

int main()
{
    BaseballData    baseball_data;
    FootballInfo    football_info;
    VolleyballStats volleyball_stats;

    AttendanceReport report;

    report.print(baseball_data,    "Baseball");
    report.print(football_info,    "Football");
    report.print(volleyball_stats, "Volleyball");

    return 0;
}
