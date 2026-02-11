#ifndef QUICKSORT_MT_YIELD_H_
#define QUICKSORT_MT_YIELD_H_

#include <condition_variable>
#include <mutex>
#include <stack>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

class Quicksort_MT_Yield
{
public:
    Quicksort_MT_Yield(int *const d, const int s, const int t)
        : data(d), size(s), thread_count(t), active_workers(0), done(false)
    {
        if (thread_count < 1)
            throw std::invalid_argument("thread_count must be >= 1");
    }

    void sort() { sort_MT_with_yield(); }
    bool verify_sorted() const;

private:
    int *data;
    int size;
    int thread_count;

    // Shared resources among worker threads.
    std::stack<std::pair<int, int>> subarray_stack;
    std::mutex mtx;
    std::condition_variable cv;
    int active_workers;
    bool done;

    void swap_values_at(int index1, int index2);
    int partition(int left_index, int right_index);
    void sort_MT_with_yield();
    void worker_thread();
};

#endif
