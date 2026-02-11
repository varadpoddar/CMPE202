#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Quicksort_MT.h"

using namespace std;
using namespace std::chrono;

int main()
{
    const int DATA_SIZE = 1000000;
    const int max_thread_MT = 24;
    int *data = new int[DATA_SIZE];
    long long baseline_ms = -1;

    srand(time(0));
    for (int i = 0; i < DATA_SIZE; i++)
        data[i] = rand();

    cout << "Problem 3: Multithreaded Quicksort \n";
    cout << left << setw(10) << "Threads"
         << setw(15) << "Time(ms)"
         << setw(18) << "Lock Wait(ms)"
         << setw(18) << "Idle Wait(ms)"
         << setw(20) << "% change vs 1T" << '\n';
    cout << string(81, '-') << '\n';

    for (int threads = 1; threads <= max_thread_MT; threads++)
    {
        int *data_copy = new int[DATA_SIZE];
        copy(data, data + DATA_SIZE, data_copy);
        Quicksort_MT qsorter(data_copy, DATA_SIZE, threads);

        auto start_time = steady_clock::now();
        qsorter.sort();
        auto end_time = steady_clock::now();
        long long ms = duration_cast<milliseconds>(end_time - start_time).count();

        if (!qsorter.verify_sorted())
        {
            cerr << "ERROR: sort failed at thread count " << threads << '\n';
            delete[] data;
            return 1;
        }

        if (threads == 1)
            baseline_ms = ms;

        double pct_change = 0.0;
        if (baseline_ms > 0)
        {
            pct_change = 100.0 * (static_cast<double>(ms - baseline_ms) / baseline_ms);
        }

        long long lock_ms = qsorter.get_lock_wait_us() / 1000;
        long long idle_ms = qsorter.get_idle_wait_us() / 1000;

        cout << left << setw(10) << threads
             << setw(15) << ms
             << setw(18) << lock_ms
             << setw(18) << idle_ms
             << fixed << showpos << setprecision(2) << pct_change << "%" << noshowpos << '\n';

        delete[] data_copy;
    }

    delete[] data;
    return 0;
}
