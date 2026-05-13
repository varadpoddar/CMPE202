#ifndef DININGPHILOSOPHERS_TIMELINE_POLLSTER_H
#define DININGPHILOSOPHERS_TIMELINE_POLLSTER_H

#include <thread>
#include "Philosopher.h"

using namespace std;

/**
 * The pollster polls the philosophers each second
 * and prints the time index, the number of servings
 * in the central bowl, and the state of each philosopher.
 */
class Pollster
{
public:
    Pollster(Philosopher *(*philosophers),
             int philosophers_count,
             atomic<int>& center_bowl_servings,
             atomic<int>& participating_count);

    ~Pollster();

private:
    int time_index;
    int philosophers_count;
    Philosopher *(*philosophers);
    atomic<int>& center_bowl_servings;
    atomic<int>& participating_count;
    thread polling_thread;

    void poll_philosophers();
    void print_states();
};


#endif //DININGPHILOSOPHERS_TIMELINE_POLLSTER_H