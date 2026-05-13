#include "BaseballData.h"
#include "FootballData.h"
#include "VolleyballData.h"
#include "AttendanceReport.h"

int main()
{
    BaseballData   baseball_data;
    FootballData   football_data;
    VolleyballData volleyball_data;

    AttendanceReport report;

    report.print(baseball_data,   "Baseball");
    report.print(football_data,   "Football");
    report.print(volleyball_data, "Volleyball");

    return 0;
}
