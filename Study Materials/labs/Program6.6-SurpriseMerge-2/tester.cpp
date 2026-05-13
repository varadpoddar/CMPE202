#include <iostream>
#include "SortedList.h"

using namespace std;

int main()
{
    SortedList list1 {2, 5, 5, 5, 7, 11, 11, 11, 13, 13};
    SortedList list2 {0, 1, 2, 2, 2, 2, 4, 4, 5, 6, 7, 7, 9, 11};

    cout << "List 1:" << list1 << endl;
    cout << "List 2:" << list2 << endl;

    SortedList merged_list;
    SortedList::merge_and_deduplicate(list1, list2, merged_list);
    cout << "Merged:" << merged_list << endl;

    return 0;
}
