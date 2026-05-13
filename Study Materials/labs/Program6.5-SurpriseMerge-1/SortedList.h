#ifndef SORTEDLIST_H_
#define SORTEDLIST_H_

#include <iostream>
#include <vector>

using namespace std;

class SortedList : public vector<int>
{
public:
    SortedList() {}

    SortedList(const initializer_list<int> init_list)
        : vector<int>(init_list) {}

    static void merge(const SortedList& list1,
                      const SortedList& list2,
                            SortedList& merged_list);
};

inline ostream& operator <<(ostream& ostr, const SortedList& list)
{
    for (int i : list) cout << " " << i;
    return ostr;
}

#endif /* SORTEDLIST_H_ */
