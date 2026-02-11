#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <chrono>

#include "Quicksort_MT.h"

using namespace std;
using namespace std::chrono;

int main()
{
    const int DATA_SIZE = 1000000;
    const int max_thread_MT = 24;
    int *data = new int[DATA_SIZE];

    srand(time(0));
    for (int i = 0; i < DATA_SIZE; i++)
        data[i] = rand();

        for (int threads = 1; threads <= max_thread_MT; threads++)
    {
        int *data_copy = new int[DATA_SIZE];
        copy(data, data + DATA_SIZE, data_copy);
        Quicksort_MT qsorter(data_copy, DATA_SIZE, threads);

        auto start_time = steady_clock::now();
        qsorter.sort();
        auto end_time = steady_clock::now();

        cout << (qsorter.verify_sorted() ? "SORTED" : "ERROR") << endl;
        long ms = duration_cast<milliseconds>(end_time - start_time).count();
        printf("%20ld ms\n", ms);
    }

    delete[] data;
    return 0;
}
