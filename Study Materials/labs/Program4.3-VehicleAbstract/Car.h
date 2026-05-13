#ifndef CAR_H_
#define CAR_H_

#include <iostream>
#include "MotorVehicle.h"

using namespace std;

class Car : public MotorVehicle
{
public:
    virtual ~Car() {}

private:
    virtual void start_engine() override
    {
        cout << "car starts engine" << endl;
    }

    virtual void stop_engine() override
    {
        cout << "car stops engine" << endl;
    }
};

#endif /* CAR_H_ */
