#include <iostream>
#include <iomanip>
#include <string>
#include "EventMaker.h"
#include "BaseballReporter.h"
#include "FanClubReport.h"

using namespace std;

void FanClubReport::update(const string name, const int outs)
{
    if (name != idol) return;

    Event  *event = reporter->get_current_event();
    int     hit   = event->get_hit();

    switch (hit)
    {
        case 0: what = "an out";   break;
        case 1: what = "a single"; break;
        case 2: what = "a double"; break;
        case 3: what = "a triple"; break;
        case 4: what = "a homer";  break;

        default: what = ""; break;
    }

    reporter->detach(this);
}

void FanClubReport::print_report() const
{
    cout << endl << endl;
    cout << "FANCLUB BULLETIN" << endl;
    cout << "The first attempt by " << idol
         << " resulted in " << what << "." << endl;
}
