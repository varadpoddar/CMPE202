#ifndef FUNDRAISER_H_
#define FUNDRAISER_H_

#include "Alumni.h"
#include "BoosterClubs.h"
#include "Students.h"

class FundRaiser
{
public:
    void do_fund_raising()
    {
        Alumni alumni;
        BoosterClubs clubs;
        Students students;

        alumni.send_solicitations();
        clubs.schedule_meetings();
        students.collect_fees();
    }
};

#endif /* FUNDRAISER_H_ */
