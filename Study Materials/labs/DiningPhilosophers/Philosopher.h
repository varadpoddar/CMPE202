#ifndef DININGPHILOSOPHERS_PHILOSOPHER_H
#define DININGPHILOSOPHERS_PHILOSOPHER_H

#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

enum class PhilosopherState
{
    Arrived, Thinking, Waiting, Filling, Eating, Left
};

/**
 * A philosopher who repeatedly thinks,
 * fills his individual bowl, and eats.
 */
class Philosopher
{
public:
    Philosopher() : servings_eaten(0)
    {
        state.store(PhilosopherState::Arrived);
    }

    ~Philosopher() = default;

    void increment_servings_eaten() { ++servings_eaten; }
    int get_servings_eaten() const { return servings_eaten; }
    atomic<PhilosopherState> *get_state() { return &state; }
    mutex *get_mutex() { return &mtx; }
    condition_variable *get_cv() { return &cv; }

    /**
     * Return whether the philosopher is using chopsticks,
     * i.e., while filling an individual bowl or eating.
     * @return true if using chopsticks; else false.
     */
    bool using_chopstick() const
    {
        PhilosopherState ps = state.load();

        return    (ps == PhilosopherState::Filling)
               || (ps == PhilosopherState::Eating);
    }

private:
    int servings_eaten;
    atomic<PhilosopherState> state;

    // Individual mutex and condition variable that the
    // philosopher waits on for available chopsticks.
    mutex mtx;
    condition_variable cv;
};

#endif //DININGPHILOSOPHERS_PHILOSOPHER_H