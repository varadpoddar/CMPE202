#ifndef BASEBALLDATA_H_
#define BASEBALLDATA_H_

#include <vector>
#include <random>
#include <time.h>

using namespace std;

class BaseballData
{
public:
    BaseballData() : normal(normal_distribution<double>(0.0, 1.75))
    {
        random_number_generator.seed(time(NULL));
        generate_hits();
    }

    vector<int> get_hits() const { return hits; }

private:
    vector<int> hits;

    default_random_engine random_number_generator;
    normal_distribution<double> normal;

    void generate_hits();
};

#endif /* BASEBALLDATA_H_ */
