#ifndef QUICKSORT_MT_H_
#define QUICKSORT_MT_H_

#include <iomanip>

using namespace std;

class Quicksort_MT
{
public:
    Quicksort_MT(int *const d, const int s, const int thread_MT) : data(d), size(s), thread_MT(thread_MT) {};

    void sort() { sort_NR(); }

    bool verify_sorted();

private:
    int *data;
    int size;
    int thread_MT;

    void swap_values_at(const int index1, const int index2);
    int partition(const int left_index, const int right_index);
    void sort_NR();
};

#endif
