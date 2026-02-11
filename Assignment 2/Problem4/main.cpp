#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "Quicksort_MT_Yield.h"

using namespace std;
using namespace std::chrono;

int main()
{
    const int DATA_SIZE = 1000000;
    const int MAX_THREADS = 24;

    int *data = new int[DATA_SIZE];
    long long baseline_ms = -1;

    srand((unsigned int)time(0));
    for (int i = 0; i < DATA_SIZE; i++)
        data[i] = rand();

    cout << "Problem 4: Multithreaded Quicksort with yields\n";
    cout << left << setw(10) << "Threads"
         << setw(15) << "Time(ms)"
         << setw(20) << "% change vs 1T" << '\n';
    cout << string(45, '-') << '\n';

    for (int threads = 1; threads <= MAX_THREADS; threads++)
    {
        int *data_copy = new int[DATA_SIZE];
        copy(data, data + DATA_SIZE, data_copy);

        Quicksort_MT_Yield qsorter(data_copy, DATA_SIZE, threads);

        auto start_time = steady_clock::now();
        qsorter.sort();
        auto end_time = steady_clock::now();
        long long ms = duration_cast<milliseconds>(end_time - start_time).count();

        if (!qsorter.verify_sorted())
        {
            cerr << "ERROR: sort failed at thread count " << threads << '\n';
            delete[] data_copy;
            delete[] data;
            return 1;
        }

        if (threads == 1)
            baseline_ms = ms;

        double pct_change = 0.0;
        if (baseline_ms > 0)
            pct_change = 100.0 * (static_cast<double>(ms - baseline_ms) / baseline_ms);

        cout << left << setw(10) << threads
             << setw(15) << ms
             << fixed << showpos << setprecision(2) << pct_change << "%" << noshowpos << '\n';

        delete[] data_copy;
    }

    delete[] data;
    return 0;
}
