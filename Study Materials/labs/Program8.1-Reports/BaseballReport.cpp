#include <iostream>
#include <iomanip>
#include "BaseballData.h"
#include "BaseballReport.h"

using namespace std;

void BaseballReport::print_header() const
{
    cout << title << endl;
    cout << endl;
}

void BaseballReport::acquire_data()
{
    BaseballData data;
    hits = data.get_hits();
}

void BaseballReport::analyze_data()
{
    singles = doubles = triples = homers = 0;

    for (int hit : hits)
    {
        switch (hit)
        {
            case 1: singles++; break;
            case 2: doubles++; break;
            case 3: triples++; break;
            case 4: homers++;  break;

            default: break;
        }
    }
}

void BaseballReport::print_bar(const char ch, const int count) const
{
    for (int i = count; i > 0; i--) cout << ch;
    cout << endl;
}

void BaseballReport::print_report() const
{
    cout << setw(2) << singles << " singles" << endl;
    cout << setw(2) << doubles << " doubles" << endl;
    cout << setw(2) << triples << " triples" << endl;
    cout << setw(2) << homers  << " homers"  << endl;
    cout << endl;
    cout << "         ....5...10...15...20...25...30" << endl;
    cout << "Singles: "; print_bar('S', singles);
    cout << "Doubles: "; print_bar('D', doubles);
    cout << "Triples: "; print_bar('T', triples);
    cout << " Homers: "; print_bar('H', homers);
}

void BaseballReport::print_footer() const
{
    cout << endl;
    cout << "End of report" << endl;
}
