#include "SortedList.h"

void SortedList::merge(const SortedList& list1,
                       const SortedList& list2,
                             SortedList& merged_list)
{
    size_t size1 = list1.size();
    size_t size2 = list2.size();

    int i1 = 0;
    int i2 = 0;

    while ((i1 < size1) || (i2 < size2))
    {
        if (   (i1 < size1)
            && ((i2 == size2) || (list1[i1] <= list2[i2])))
        {
            merged_list.push_back(list1[i1]);
            i1++;
        }
        else
        {
            merged_list.push_back(list2[i2]);
            i2++;
        }
    }

    int i = 0;

    while (i < merged_list.size())
    {
        int j = i + 1;

        while (j < merged_list.size())
        {
            if (merged_list[i] == merged_list[j])
            {
                merged_list.erase(merged_list.begin() + j);
            }
            else j++;
        }

        i++;
    }
}
