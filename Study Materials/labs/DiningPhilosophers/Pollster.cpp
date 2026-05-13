#include <iostream>
#include "Pollster.h"

using namespace std;

/**
 * Constructor.
 * @param phs the array of philosophers.
 * @param cbs the number of center bowl servings.
 * @param pc the count of participating philosophers.
 */
Pollster::Pollster(Philosopher *(*phs), int count,
                   atomic<int>& cbs, atomic<int>& pc )
    : time_index(-1), philosophers(phs),
      philosophers_count(count),
      center_bowl_servings(cbs),
      participating_count(pc)
{
    // Spawn the polling thread.
    polling_thread = thread(&Pollster::poll_philosophers, this);
}

/**
 * Destructor.
 */
Pollster::~Pollster()
{
    // Take a final poll before joining the thread.
    print_states();
    polling_thread.join();
}

/**
 * Poll the philosophers for their current states once per second.
 */
void Pollster::poll_philosophers()
{
    while (participating_count.load() > 0)
    {
        print_states();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

/**
 * Print time index, number of remaining services in the center bowl,
 * and the state of each philosopher.
 */
void Pollster::print_states()
{
    // Time index and the number of remaining services
    // in the center bowl.
    printf("%3d%8d   ", ++time_index, center_bowl_servings.load());

    // Poll each philosopher's state.
    for (int i = 0; i < philosophers_count; i++)
    {
        PhilosopherState ps = philosophers[i]->get_state()->load();

        cout << "    ";

        if      (ps == PhilosopherState::Arrived)  cout << "Arrived  ";
        else if (ps == PhilosopherState::Thinking) cout << "Thinking ";
        else if (ps == PhilosopherState::Waiting)  cout << "Waiting  ";
        else if (ps == PhilosopherState::Filling)  cout << "*Filling*";
        else if (ps == PhilosopherState::Eating)   cout << "*Eating* ";
        else if (ps == PhilosopherState::Left)     cout << "--Left-- ";

        cout << "  ";
    }
    cout << endl;
}
