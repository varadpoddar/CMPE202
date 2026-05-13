#include <iostream>
#include <chrono>
#include <thread>
#include <shared_mutex>

#include "Meter.h"

using namespace std;

Meter::Meter()
{
    setting = 0;
    active_technicians_count = TECHNICIANS_COUNT;
    srand(time(0));
    start_time = steady_clock::now();
    ok_to_log = false;

    // Spawn technician threads (the writers).
    for (int i = 0; i < TECHNICIANS_COUNT; i++)
    {
        technicians[i] = thread(&Meter::set_meter, this, i + 1);
    }

    // Spawn logger threads (the readers).
    for (int i = 0; i < LOGGERS_COUNT; i++)
    {
        loggers[i] = thread(&Meter::log_meter, this, i + 1);
    }
}

Meter::~Meter()
{
    // Wait for the logger threads to complete.
    for (int i = 0; i < LOGGERS_COUNT; i++)
    {
        loggers[i].join();
    }

    // Wait for the technician threads to complete.
    for (int i = 0; i < TECHNICIANS_COUNT; i++)
    {
        technicians[i].join();
    }

    cout << endl << "Program done!" << endl;
}

/**
 * Writer thread: Set the value of the meter.
 * @param thread_id the ID of this thread.
 */
void Meter::set_meter(const int thread_id)
{
    // Each technician sets the meter multiple times.
    for (int turn = 1; turn <= TECHNICIAN_TURNS; turn++)
    {
        // Simulate pausing between settings.
        int sleep_time = rand()%(  MAX_TECHNICIAN_SLEEP_TIME
                                 - MIN_TECHNICIAN_SLEEP_TIME)
                       + MIN_TECHNICIAN_SLEEP_TIME;
        this_thread::sleep_for(chrono::seconds(sleep_time));

        // Allow only one thread (technician or logger)
        // at a time in this critical region.
        {
            unique_lock<shared_mutex> writing_lock(meter_mutex);
            {
                printf("%02d TECH #%d:", elapsed_seconds(), thread_id);

                setting = rand()%MAX_SETTING_LEVEL + 1;

                // Simulate taking 1 second per setting level.
                for (int n = 1; n <= setting; n++)
                {
                    this_thread::sleep_for(
                           chrono::seconds(TECHNICIAN_SET_TIME));
                    printf("%2d", n); cout.flush();
                }
                cout << endl;

                ok_to_log = true;

                if (turn == TECHNICIAN_TURNS)
                {
                    printf("%02d TECH #%d: done!\n",
                           elapsed_seconds(), thread_id);

                    active_technicians_count--;
                }
            }
        }

        this_thread::yield();  // necessary?
    }
}

/**
 * Reader thread: Log the current value of the meter.
 * @param thread_id the ID of this thread.
 */
void Meter::log_meter(const int thread_id)
{
    while (active_technicians_count > 0)
    {
        // Simulate pausing between loggings.
        this_thread::sleep_for(
            chrono::seconds(rand()%MAX_LOGGER_SLEEP_TIME + 1));

        // OK to log after the meter is set the first time.
        if (ok_to_log)
        {
            // Allow multiple simultaneous logger threads,
            // but no technician threads in this critical region.
            shared_lock<shared_mutex> reading_lock(meter_mutex);
            {
                lock_guard<mutex> printing_lock(print_mutex);
                {
                    printf("%*s%02d LOGGER #%d: logging %d\n",
                           LOGGER_PRINT_MARGIN, " ",
                           elapsed_seconds(), thread_id, setting);
                }
            }
        }

        this_thread::yield();  // necessary?
    }
}
