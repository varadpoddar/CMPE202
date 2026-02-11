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
 * - A single unique mutex (mtx) guards all accesses to subarray_stack, active_workers, and when done is set to true.
 * - Partitioning work is done outside the lock to reduce friction.
 *
 * Synchronization approach:
 * - condition_variable (cv) blocks idle workers until work appears or sorting is complete.
 * - Workers call notify_all() after publishing new tasks or setting done=true.
 * - Completion is detected when subarray_stack is empty and active_workers == 0.
 *
 * Yielding strategy:
 * - After a worker thread partitions a subarray and pushes new tasks, it yields to allow
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
    while (true)
    {
        int left = 0;
        int right = -1;

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]()
                    { return done || !subarray_stack.empty(); });

            if (done && subarray_stack.empty())
                return;

            std::pair<int, int> bounds = subarray_stack.top();
            subarray_stack.pop();
            left = bounds.first;
            right = bounds.second;
            ++active_workers;
        }

        if (left < right)
        {
            int pivot_index = partition(left, right);

            bool pushed_any = false;

            std::unique_lock<std::mutex> lock(mtx);
            if (left < pivot_index - 1)
            {
                subarray_stack.push({left, pivot_index - 1});
                pushed_any = true;
            }
            if (pivot_index + 1 < right)
            {
                subarray_stack.push({pivot_index + 1, right});
                pushed_any = true;
            }

            --active_workers;
            if (subarray_stack.empty() && active_workers == 0)
                done = true;

            cv.notify_all();
            lock.unlock();

            // Strategic yield: yield only after publishing new work.
            if (pushed_any)
            {
                std::this_thread::yield();
            }
        }
        else
        {
            std::unique_lock<std::mutex> lock(mtx);
            --active_workers;

            if (subarray_stack.empty() && active_workers == 0)
                done = true;

            cv.notify_all();
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

    {
        std::lock_guard<std::mutex> lock(mtx);
        cv.notify_all();
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
