#include <vector>
#include <random>
#include "BaseballData.h"

using namespace std;

void BaseballData::generate_hits()
{
    int outs = 0;

    while (outs < 27)
    {
        double r   = normal(random_number_generator);
        int    hit = static_cast<int>(abs(r));

        if (hit > 4) hit = 4;

        if (hit != 0) hits.push_back(hit);
        else          outs++;
    }
}
