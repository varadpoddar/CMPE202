#include <iostream>
#include <thread>
#include <mutex>

#include "Philosopher.h"
#include "DiningPhilosophers.h"
#include "Pollster.h"

using namespace std;

/**
 * Constructor.
 * @param cnt the number of philosophers.
 * @param srv the number of servings in the central bowl.
 */
DiningPhilosophers::DiningPhilosophers(const int cnt, const int srv)
    : philosophers_count(cnt), // time_index(-1),
      philosophers(new Philosopher *[philosophers_count]),
      philosopher_threads(new thread[philosophers_count])
{
    central_bowl_servings.store(srv);
    participating_count.store(cnt);

    // Print column headers.
    cout << "Time  Servings";
    for (int i = 0; i < philosophers_count; i++)
    {
        cout << "  Philosopher " << i;
    }
    cout << endl;

    // Create philosopher objects.
    for (int i = 0; i < philosophers_count; i++)
    {
        philosophers[i] = new Philosopher();
    }

    // Create the pollster.
    pollster = new Pollster(philosophers, philosophers_count,
                            central_bowl_servings, participating_count);

    // Spawn the philosopher threads.
    for (int i = 0; i < philosophers_count; i++)
    {
        philosopher_threads[i] = thread(&DiningPhilosophers::run,
                                        this, i, philosophers[i]);
    }
}

/**
 * Destructor.
 */
DiningPhilosophers::~DiningPhilosophers()
{
    // Join all the philosopher threads.
    for (int i = 0; i < philosophers_count; i++)
    {
        philosopher_threads[i].join();
    }

    // This will cause a final poll.
    delete pollster;

    // How many servings did each philosopher eat?
    cout << endl;
    cout << "Servings eaten";
    for (int i = 0; i < philosophers_count; i++)
    {
        printf("%8d       ", philosophers[i]->get_servings_eaten());
        delete philosophers[i];
    }
    cout << endl;

    delete[] philosophers;
    delete[] philosopher_threads;
}

/**
 * Run the simulation in real time. One second = one minute.
 * Until all the servings in the central bowl are gone,
 * each philosopher is in the loop
 *     thinking - fill individual bowl - eating
 * @param thread_id the ID of the philosopher thread.
 * @param philosopher the philosopher of the thread.
 */
void DiningPhilosophers::run(const int thread_id,
                             Philosopher *const philosopher)
{
    // The philosopher counterclockwise to the left.
    int left_index =
            (thread_id + philosophers_count - 1)%philosophers_count;
    Philosopher *left_philosopher = philosophers[left_index];

    // The philosopher clockwise to the right.
    int right_index = (thread_id + 1)%philosophers_count;
    Philosopher *right_philosopher = philosophers[right_index];

    // Yield to let the pollster do its first poll.
    this_thread::yield();

    // Start in the thinking state.
    philosopher->get_state()->store(PhilosopherState::Thinking);

    // Main loop until all the noodles in the central bowl are gone.
    do
    {
        // Thinking.
        this_thread::sleep_for(
            chrono::seconds(rand()%(MAX_THINKING_TIME
                                    - MIN_THINKING_TIME + 1)
                            + MIN_THINKING_TIME)
        );

        // The philosopher's individual mutex and condition variable
        // for waiting for the chopsticks to become available.
        mutex *mtx = philosopher->get_mutex();
        condition_variable *cv = philosopher->get_cv();

        // Go into the waiting state.
        philosopher->get_state()->store(PhilosopherState::Waiting);
        unique_lock<mutex> lock(*mtx);
        {
            // Wait while both chopsticks on either side are in use.
            while (   left_philosopher->using_chopstick()
                   || right_philosopher->using_chopstick()
                  )
            {
                // Wait on the philosopher's condition variable.
                cv->wait(lock);
            }
        }

        // Still more servings left in the central bowl?
        if (central_bowl_servings.load() > 0)
        {
            // Go into the filling state and fill
            // the philosopher's individual bowl.
            --central_bowl_servings;
            philosopher->get_state()->store(PhilosopherState::Filling);
            this_thread::sleep_for(chrono::seconds(FILLING_TIME));

            // Go into the eating state and eat.
            philosopher->get_state()->store(PhilosopherState::Eating);
            this_thread::sleep_for(
                chrono::seconds(rand()%(MAX_EATING_TIME
                                        - MIN_EATING_TIME + 1)
                                + MIN_EATING_TIME)
            );
            philosopher->increment_servings_eaten();

            // Done eating. Notify the neighboring philosophers that the
            // chopsticks are now available. Return to the thinking state.
            left_philosopher->get_cv()->notify_one();
            right_philosopher->get_cv()->notify_one();
            philosopher->get_state()->store(PhilosopherState::Thinking);
        }
    } while (central_bowl_servings.load() > 0);

    // The central bowl is now empty. Go into the left state and leave.
    philosopher->get_state()->store(PhilosopherState::Left);
    --participating_count;

    // Notify any philosophers who may still be waiting.
    for (int i = 0; i < philosophers_count; i++)
    {
        philosophers[i]->get_cv()->notify_one();
    }
}