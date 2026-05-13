#ifndef TRUCK_H_
#define TRUCK_H_

#include <iostream>
#include "MotorVehicle.h"

using namespace std;

class Truck : public MotorVehicle
{
public:
    virtual ~Truck() {}

private:
    virtual void start_engine() override
    {
        cout << "truck starts engine" << endl;
    }

    virtual void stop_engine() override
    {
        cout << "truck stops engine" << endl;
    }

    virtual void turn_left() override
    {
        cout << "truck turns left" << endl;
    }

    virtual void turn_right() override
    {
        cout << "truck turns right" << endl;
    }
};

#endif /* TRUCK_H_ */
