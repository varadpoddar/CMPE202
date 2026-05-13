#include "SortedList.h"

void SortedList::merge_and_deduplicate(const SortedList& list1,
                                       const SortedList& list2,
                                             SortedList& merged_list)
{
    size_t size1 = list1.size();
    size_t size2 = list2.size();

    size_t merged_size = 0;

    int i1 = 0;
    int i2 = 0;

    // Merge the contents of list1 and list2
    // into merged_list without entering any
    // duplicate values.
    while ((i1 < size1) || (i2 < size2))
    {
        if (   (i1 < size1)
            && ((i2 == size2) || (list1[i1] <= list2[i2])))
        {
            if (   (merged_size == 0)
                || (list1[i1] != merged_list[merged_size-1]))
            {
                merged_list.push_back(list1[i1]);
                merged_size++;
            }
            i1++;
        }
        else
        {
            if (   (merged_size == 0)
                || (list2[i2] != merged_list[merged_size-1]))
            {
                merged_list.push_back(list2[i2]);
                merged_size++;
            }
            i2++;
        }
    }
}
