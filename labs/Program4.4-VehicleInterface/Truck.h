#ifndef TRUCK_H_
#define TRUCK_H_

#include <iostream>
#include "MotorVehicleInterface.h"

using namespace std;

class Truck : public MotorVehicleInterface
{
public:
    virtual ~Truck() {}

    virtual void drive() override
    {
        start_engine();
        accelerate();
        turn_left();
        turn_right();
        apply_brakes();
        stop_engine();

        cout << endl;
    }

private:
    virtual void start_engine() override
    {
        cout << "truck starts engine" << endl;
    }

    virtual void stop_engine() override
    {
        cout << "truck stops engine" << endl;
    }

    virtual void accelerate() override
    {
        cout << "truck accelerates" << endl;
    }

    virtual void turn_left() override
    {
        cout << "truck turns left" << endl;
    }

    virtual void turn_right() override
    {
        cout << "truck turns right" << endl;
    }

    virtual void apply_brakes() override
    {
        cout << "truck applies brakes" << endl;
    }

    Brake brakes[4];
    Engine engine;
    Direction heading;
    int speed;
};

#endif /* TRUCK_H_ */
