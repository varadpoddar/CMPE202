#include <iomanip>
#include <thread>
#include "Quicksort_NR.h"

using namespace std;

void Quicksort_NR::swap_values_at(const int index1, const int index2)
{
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

int Quicksort_NR::partition(const int left_index, const int right_index)
{
    // Choose the pivot value.
    int middle_index = (left_index + right_index)/2;
    int pivot_value  = data[middle_index];

    // Swap out the pivot value to the right end.
    swap_values_at(middle_index, right_index);

    int i = left_index - 1;
    int j = right_index;

    // Loop until i and j cross.
    while (i < j)
    {
        // Move i to the rightl.
        do
        {
            i++;
        } while ((i < right_index) && (data[i] < pivot_value));

        // Move j to the left.
        do
        {
            j--;
        } while ((j >= left_index) && (data[j] > pivot_value));

        // Swap values after i and j stopped moving;
        if (i < j) swap_values_at(i, j);
    }

    // Swap the pivot value back in.
    swap_values_at(i, right_index);

    return i;
}

void Quicksort_NR::sort_NR()
{
    stack<pair<int,int>> subarray_stack;

    // Start with the whole array bounds.
    subarray_stack.push({0, size - 1});

    while (!subarray_stack.empty())
    {
        auto [left, right] = subarray_stack.top();
        subarray_stack.pop();

        if (left >= right) continue;

        int pivot_index = partition(left, right);

        // Push bounds of left subarray
        if (left < pivot_index - 1)
            subarray_stack.push({left, pivot_index - 1});

        // Push bounds of right subarray
        if (pivot_index + 1 < right)
            subarray_stack.push({pivot_index + 1, right});
    }
}

bool Quicksort_NR::verify_sorted()
{
    for (int i = 0; i < size - 1; i++)
    {
        if (data[i] > data[i+1]) return false;
    }

    return true;
}
