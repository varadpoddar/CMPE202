#ifndef APPOINTMENTS_H_
#define APPOINTMENTS_H_

#include <vector>
#include "Date.h"

using namespace std;

class Appointments
{
public:
    vector<Date *> get_dates() const { return dates; }

    Date *at(const int index) const { return dates[index]; }

    /**
     * Append a pointer to a Date object.
     * @param date the pointer to append.
     */
    void append(Date * const date)  { dates.push_back(date); }

    /**
     * Insert a pointer to a Date object at the given index.
     * @param index the index.
     * @param date the pointer to insert.
     */
    void insert(const int index, Date * const date)
    {
        dates.insert(dates.begin() + index, date);
    }

    /**
     * Remove the pointer to a Date object at the given index.
     * @param index the index.
     */
    void remove(const int index)
    {
        dates.erase(dates.begin() + index);
    }

private:
    vector<Date *> dates;
};

#endif /* APPOINTMENTS_H_ */
