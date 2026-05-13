#include "BaseballData.h"
#include "FootballData.h"
#include "VolleyballData.h"
#include "FootballInfo.h"
#include "VolleyballStats.h"
#include "AttendanceReport.h"

int main()
{
    BaseballData    baseball_data;
    FootballInfo    football_info;
    VolleyballStats volleyball_stats;

    FootballData   football_data(football_info);
    VolleyballData volleyball_data(volleyball_stats);

    AttendanceReport report;

    report.print(baseball_data,   "Baseball");
    report.print(football_data,   "Football");
    report.print(volleyball_data, "Volleyball");

    return 0;
}
