#include "Quicksort_MT_Yield.h"

/*
 *
 * Shared resources:
 * - subarray_stack: global work queue of subarray bounds (left, right).
 * - active_workers: number of threads currently processing a popped task.
 * - done: global completion flag that tells workers to stop.
 * - data array: shared container being sorted; threads work on disjoint subarrays.
 *
 * Critical regions:
 * - Any push/pop on subarray_stack.
 * - Any read/write of active_workers.
 * - Any read/write of when done is set to true.
 *
 * How critical regions are protected:
 * - A single mutex (mtx) guards all accesses to subarray_stack, active_workers, and done.
 * - Partitioning work is done outside the lock to reduce contention.
 *
 * Synchronization approach (Yield Wait):
 * - Instead of blocking on a condition_variable, idle workers spin in a
 *   yield loop: lock the mutex, check for work, unlock, then yield().
 * - std::this_thread::yield() surrenders the current time slice so the OS
 *   can schedule other threads, but the thread remains runnable and retries
 *   immediately when rescheduled.
 * - Completion is detected when subarray_stack is empty and active_workers == 0.
 * - Trade-off vs lock wait: lower wake-up latency but higher CPU usage while idle.
 */

void Quicksort_MT_Yield::swap_values_at(const int index1, const int index2)
{
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

int Quicksort_MT_Yield::partition(const int left_index, const int right_index)
{
    int middle_index = (left_index + right_index) / 2;
    int pivot_value = data[middle_index];

    swap_values_at(middle_index, right_index);

    int i = left_index - 1;
    int j = right_index;

    while (i < j)
    {
        do
        {
            i++;
        } while ((i < right_index) && (data[i] < pivot_value));

        do
        {
            j--;
        } while ((j >= left_index) && (data[j] > pivot_value));

        if (i < j)
            swap_values_at(i, j);
    }

    swap_values_at(i, right_index);
    return i;
}

void Quicksort_MT_Yield::worker_thread()
{
    using clk = std::chrono::steady_clock;

    while (true)
    {
        int left = 0;
        int right = -1;

        // Yield wait: spin-yield loop until work is available or sorting is done.
        auto idle_start = clk::now();
        while (true)
        {
            auto lock_start = clk::now();
            std::unique_lock<std::mutex> lock(mtx);
            auto lock_end = clk::now();
            total_lock_wait_us += std::chrono::duration_cast<std::chrono::microseconds>(
                                      lock_end - lock_start).count();

            if (done && subarray_stack.empty())
            {
                total_idle_wait_us += std::chrono::duration_cast<std::chrono::microseconds>(
                                          clk::now() - idle_start).count();
                return;
            }

            if (!subarray_stack.empty())
            {
                total_idle_wait_us += std::chrono::duration_cast<std::chrono::microseconds>(
                                          clk::now() - idle_start).count();
                std::pair<int, int> bounds = subarray_stack.top();
                subarray_stack.pop();
                left = bounds.first;
                right = bounds.second;
                ++active_workers;
                break;
            }

            lock.unlock();
            std::this_thread::yield(); // Yield wait: give up time slice and retry.
        }

        if (left < right)
        {
            int pivot_index = partition(left, right);

            auto lock_start = clk::now();
            std::unique_lock<std::mutex> lock(mtx);
            auto lock_end = clk::now();
            total_lock_wait_us += std::chrono::duration_cast<std::chrono::microseconds>(
                                      lock_end - lock_start).count();

            if (left < pivot_index - 1)
                subarray_stack.push({left, pivot_index - 1});
            if (pivot_index + 1 < right)
                subarray_stack.push({pivot_index + 1, right});

            --active_workers;
            if (subarray_stack.empty() && active_workers == 0)
                done = true;
        }
        else
        {
            auto lock_start = clk::now();
            std::unique_lock<std::mutex> lock(mtx);
            auto lock_end = clk::now();
            total_lock_wait_us += std::chrono::duration_cast<std::chrono::microseconds>(
                                      lock_end - lock_start).count();

            --active_workers;
            if (subarray_stack.empty() && active_workers == 0)
                done = true;
        }
    }
}

void Quicksort_MT_Yield::sort_MT_with_yield()
{
    if (size <= 1)
        return;

    {
        std::lock_guard<std::mutex> lock(mtx);
        done = false;
        active_workers = 0;
        total_lock_wait_us = 0;
        total_idle_wait_us = 0;

        while (!subarray_stack.empty())
            subarray_stack.pop();
        subarray_stack.push({0, size - 1});
    }

    std::vector<std::thread> workers;
    workers.reserve(thread_count);

    for (int i = 0; i < thread_count; i++)
    {
        workers.emplace_back(&Quicksort_MT_Yield::worker_thread, this);
    }

    for (std::thread &t : workers)
    {
        t.join();
    }
}

bool Quicksort_MT_Yield::verify_sorted() const
{
    for (int i = 0; i < size - 1; i++)
    {
        if (data[i] > data[i + 1])
            return false;
    }

    return true;
}
