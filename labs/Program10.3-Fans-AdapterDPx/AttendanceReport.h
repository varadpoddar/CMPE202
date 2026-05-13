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
               const string title) const
    {
        cout << title << endl;
        print_report(data);
    }

private:
    // Legacy: Cannot change!
    void print_report(const AttendanceData& data) const
    {
        cout << "  " << data.get_venue()
             << ": " << data.get_attendance() << endl;
    }
};

#endif /* ATTENDANCEREPORT_H_ */
