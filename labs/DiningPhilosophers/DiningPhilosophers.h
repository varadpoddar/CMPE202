#ifndef DININGPHILOSOPHERS_DININGPHILOSOPHERS_H
#define DININGPHILOSOPHERS_DININGPHILOSOPHERS_H

#include <thread>
#include <mutex>
#include <atomic>

#include "Philosopher.h"
#include "Pollster.h"

using namespace std;

class DiningPhilosophers
{
private:
    static constexpr int FILLING_TIME      = 1;
    static constexpr int MIN_THINKING_TIME = 3;
    static constexpr int MAX_THINKING_TIME = 6;
    static constexpr int MIN_EATING_TIME   = 2;
    static constexpr int MAX_EATING_TIME   = 4;

public:
    DiningPhilosophers(const int cnt, const int srv);
    ~DiningPhilosophers();

    void run(const int thead_id, Philosopher *const philosopher);

private:
    int philosophers_count;

    Pollster *pollster;

    // Current remaining servings in the central bowl.
    atomic<int> central_bowl_servings;

    // Current number of philosophers still participating.
    atomic<int> participating_count;

    // The dynamic array of pointers to Philosopher objects
    // and the dynamic array of philosopher threads.
    // These are parallel arrays.
    Philosopher *(*philosophers);
    thread *philosopher_threads;
};

#endif //DININGPHILOSOPHERS_DININGPHILOSOPHERS_H