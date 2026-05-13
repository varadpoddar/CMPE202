#ifndef ATHLETICSDEPT_H_
#define ATHLETICSDEPT_H_

#include <iostream>
#include "Alumni.h"
#include "BoosterClubs.h"
#include "Students.h"

using namespace std;

class AthleticsDept
{
public:
    void raise_funds()
    {
        Alumni alumni;
        BoosterClubs clubs;
        Students students;

        cout << endl << "ATHLETICS DEPARTMENT" << endl;

        alumni.send_solicitations();
        clubs.schedule_meetings();
        students.collect_fees();
    }
};

#endif /* ATHLETICSDEPT_H_ */
