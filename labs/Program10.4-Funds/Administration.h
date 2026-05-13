#ifndef ADMINISTRATION_H_
#define ADMINISTRATION_H_

#include <iostream>
#include "Alumni.h"
#include "BoosterClubs.h"
#include "Students.h"

using namespace std;

class Administration
{
public:
    void aid_fundraising()
    {
        Alumni alumni;
        BoosterClubs clubs;
        Students students;

        cout << endl << "SCHOOL ADMINISTRATION" << endl;

        alumni.send_solicitations();
        clubs.schedule_meetings();
        students.collect_fees();
    }
};

#endif /* ADMINISTRATION_H_ */
