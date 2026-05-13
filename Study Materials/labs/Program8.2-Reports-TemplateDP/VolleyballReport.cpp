#include <iostream>
#include <iomanip>
#include <vector>
#include "VolleyballData.h"
#include "VolleyballReport.h"

using namespace std;

void VolleyballReport::acquire_data()
{
    VolleyballData data;
    points = data.get_points();
}

void VolleyballReport::analyze_data()
{
    int final_index = points.size() - 1;
    team1_is_winner = points[final_index] > 0;

    for (int i = final_index; i > 0; i--)
    {
        if (   ( team1_is_winner && (points[i] < 0))
            || (!team1_is_winner && (points[i] > 0)))
        {
            losers_score = abs(points[i]);
            break;
        }
    }
}

void VolleyballReport::print_report() const
{
    cout << "Winner was Team ";
    cout << (team1_is_winner ? "1" : "2") << endl;
    cout << "The winning score was 15 to " << losers_score << endl;
    cout << endl;
    cout << "     ....5...10...15" << endl;

    int i = 0;
    for (int s : points)
    {
        cout << setw(3) << ++i << ":";

        char ch = s > 0 ? '1' : '2';
        for (int k = 0; k < abs(s); k++) cout << " ";
        cout << ch << endl;
    }
}
