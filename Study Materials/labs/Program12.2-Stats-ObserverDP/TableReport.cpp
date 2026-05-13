#include <iostream>
#include <iomanip>
#include <string>
#include "EventMaker.h"
#include "BaseballReporter.h"
#include "TableReport.h"

using namespace std;

void TableReport::update(const string name, const int outs)
{
    Event  *event = reporter->get_current_event();
    int     hit   = event->get_hit();

    if (hit_map.find(name) == hit_map.end())
    {
        hit_map[name] = new int[5] { 0, 0, 0, 0, 0 };
    }
    hit_map[name][hit]++;

    if (outs == 27) print_report();
}

void TableReport::print_report()
{
    cout << endl << endl;
    cout << "GAME HITS TABLE" << endl;
    cout << endl;

    cout << "Player     Outs   Singles Doubles Triples Homers"
         << endl;
    cout << "------------------------------------------------"
         << endl;

    for (auto it = hit_map.begin(); it != hit_map.end(); it++)
    {
        cout << setw(6) << left << it->first;

        int *hits = it->second;
        for (int i = 0; i < 5; i++)
        {
            if (hits[i] > 0) cout << setw(8) << right << hits[i];
            else             cout << "        ";
        }
        cout << endl;
    }
}
