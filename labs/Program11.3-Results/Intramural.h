#ifndef INTRAMURAL_H_
#define INTRAMURAL_H_

#include <vector>
#include "Sport.h"
#include "Hall.h"

class Intramural
{
public:
    ~Intramural()
    {
        for (Sport *sport : sports) delete sport;
        for (Hall  *hall  : halls)  delete hall;
    }

    void add_sport(Sport *sport) { sports.push_back(sport); }
    void add_hall(Hall *hall)    { halls.push_back(hall); }

    void print_scores_report() const;
    void print_activities_report() const;
    void print_winnings_report() const;

private:
    vector<Sport *> sports;
    vector< Hall *>  halls;
};

#endif /* INTRAMURAL_H_ */
