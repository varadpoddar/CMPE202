#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <chrono>

#include "Quicksort.h"

using namespace std;
using namespace std::chrono;

int main()
{
    const int DATA_SIZE = 1000000;
    int *data = new int[DATA_SIZE];

    srand(time(0));
    for (int i = 0; i < DATA_SIZE; i++) data[i] = rand();

    Quicksort qsorter(data, DATA_SIZE);

    auto start_time = steady_clock::now();
    qsorter.sort();
    auto end_time = steady_clock::now();

    cout << (qsorter.verify_sorted() ? "SORTED" : "ERROR") << endl;
    long ms = duration_cast<milliseconds>(end_time - start_time).count();
    printf("%20ld ms\n", ms);

    delete[] data;
    return 0;
}
