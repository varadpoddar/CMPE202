#ifndef VOLLEYBALLDATA_H_
#define VOLLEYBALLDATA_H_

#include <vector>
#include <random>
#include <time.h>

using namespace std;

class VolleyballData
{
public:
    VolleyballData() : uniform(uniform_int_distribution<int>(1, 2))
    {
        random_number_generator.seed(time(NULL));
        generate_points();
    }

    vector<int> get_points() const { return points; }

private:
    vector<int> points;

    default_random_engine random_number_generator;
    uniform_int_distribution<int> uniform;

    void generate_points();
};

#endif /* VOLLEYBALLDATA_H_ */
