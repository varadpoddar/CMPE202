#include <iostream>
#include <iomanip>
#include <map>
#include "SortedList.h"

using namespace std;

void print_frequencies(const SortedList& merged_list);

int main()
{
    SortedList list1 {2, 5, 5, 5, 7, 11, 11, 11, 13, 13};
    SortedList list2 {0, 1, 2, 2, 2, 2, 4, 4, 5, 6, 7, 7, 9, 11};

    cout << "List 1:" << list1 << endl;
    cout << "List 2:" << list2 << endl;

    SortedList merged_list;
    SortedList::merge(list1, list2, merged_list);
    cout << "Merged:" << merged_list << endl;

    cout << endl;
    print_frequencies(merged_list);

    return 0;
}

void print_frequencies(const SortedList& merged_list)
{
    map<int, int> freqs;

    cout << "Frequency table" << endl;

    for (int i : merged_list)
    {
        if (freqs.find(i) == freqs.end()) freqs[i] = 1;
        else                              freqs[i]++;
    }

    for (map<int, int>::iterator it = freqs.begin();
         it != freqs.end(); it++)
    {
        cout << setw(7) << it->first << ": " << it->second << endl;
    }
}
