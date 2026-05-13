#include <random>
#include "EventMaker.h"

using namespace std;

Event *EventMaker::next_event()
{
    if (outs < 27)
    {
        double r   = normal(random_number_generator);
        int    hit = static_cast<int>(abs(r));

        if (hit > 4) hit = 4;
        if (hit == 0) outs++;

        name_index = (name_index + 1)%9;

        return new Event(names[name_index], hit);
    }
    else return nullptr;
}
