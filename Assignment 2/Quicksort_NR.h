#ifndef QUICKSORT_NR_H_
#define QUICKSORT_NR_H_

#include <iomanip>

using namespace std;

class Quicksort_NR
{
public:
    Quicksort_NR(int * const d, const int s) : data(d), size(s) {};

    void sort() { sort_NR(); }

    bool verify_sorted();

private:
    int *data;
    int size;

    void swap_values_at(const int index1, const int index2);
    int partition(const int left_index, const int right_index);
    void sort_NR();
};

#endif