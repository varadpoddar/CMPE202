#ifndef QUICKSORT_MT_H_
#define QUICKSORT_MT_H_

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <stack>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

class Quicksort_MT
{
public:
    Quicksort_MT(int *const d, const int s, const int t)
        : data(d), size(s), thread_count(t), active_workers(0), done(false)
    {
        if (thread_count < 1)
            throw std::invalid_argument("thread_count must be >= 1");
    }

    void sort() { sort_MT(); }
    bool verify_sorted() const;

    // Timing accessors (microseconds).
    long long get_lock_wait_us() const { return total_lock_wait_us.load(); }
    long long get_idle_wait_us() const { return total_idle_wait_us.load(); }

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

    // Accumulated timing counters across all threads.
    std::atomic<long long> total_lock_wait_us{0};  // time waiting to acquire mutex
    std::atomic<long long> total_idle_wait_us{0};  // time waiting for work (cv.wait)

    void swap_values_at(int index1, int index2);
    int partition(int left_index, int right_index);
    void sort_MT();
    void worker_thread();
};

#endif