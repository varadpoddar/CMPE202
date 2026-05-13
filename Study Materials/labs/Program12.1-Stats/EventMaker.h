#ifndef EVENTMAKER_H_
#define EVENTMAKER_H_

#include <string>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

class Event
{
public:
    Event(const string n, const int h) : name(n), hit(h) {}

    string get_name() const { return name; }
    int    get_hit()  const { return hit; }

private:
    string name;
    int hit;
};

class EventMaker
{
public:
    EventMaker()
        : name_index(-1), outs(0),
          normal(normal_distribution<double>(0.0, 1.75))
    {
        random_number_generator.seed(time(NULL));
    }

    int get_outs() const { return outs; }

    Event *next_event();

private:
    vector<string> names = { "Al", "Beth", "Carl", "Donna", "Ed",
                             "Fran", "George", "Heidi", "Ivan" };
    int name_index;
    int outs;

    default_random_engine random_number_generator;
    normal_distribution<double> normal;
};

#endif /* EVENTMAKER_H_ */
