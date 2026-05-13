#ifndef HALL_H_
#define HALL_H_

#include "Enums.h"

using namespace std;

class Hall
{
public:
    Hall(const HallName name) : name(name), win_count(0) {}

    HallName get_name() const { return name; }

    void increment_win_count() { win_count++; }
    void print_win_count() const;

private:
    HallName name;
    int win_count;
};

#endif /* HALL_H_ */
