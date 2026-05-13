#include <iostream>
#include <iomanip>
#include <string>
#include "EventMaker.h"
#include "BaseballReporter.h"
#include "LogReport.h"

using namespace std;

void LogReport::update(const string name, const int outs)
{
    Event  *event = reporter->get_current_event();
    int     hit   = event->get_hit();
    string  what;

    switch (hit)
    {
        case 0: what = "an out";   break;
        case 1: what = "a single"; break;
        case 2: what = "a double"; break;
        case 3: what = "a triple"; break;
        case 4: what = "a homer";  break;

        default: what = ""; break;
    }

    count++;
    cout << setw(2) << count << setw(7) << name
         << " hit " << what << endl;
}
