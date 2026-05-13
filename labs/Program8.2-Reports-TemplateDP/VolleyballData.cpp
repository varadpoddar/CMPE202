#include <vector>
#include <random>
#include "VolleyballData.h"

using namespace std;

void VolleyballData::generate_points()
{
    int score1 = 0;
    int score2 = 0;

    while ((score1 < 15) && (score2 < 15))
    {
        int which_team = uniform(random_number_generator);

        if (which_team == 1)
        {
            score1++;
            points.push_back(score1);
        }
        else
        {
            score2++;
            points.push_back(-score2);
        }
    }
}
