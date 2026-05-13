#ifndef CAR_H_
#define CAR_H_

#include <iostream>
#include "MotorVehicleInterface.h"

using namespace std;

class Car : public MotorVehicleInterface
{
public:
    virtual ~Car() {}

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
        cout << "car starts engine" << endl;
    }

    virtual void stop_engine() override
    {
        cout << "car stops engine" << endl;
    }

    virtual void accelerate() override
    {
        cout << "car accelerates" << endl;
    }

    virtual void turn_left() override
    {
        cout << "car turns left" << endl;
    }

    virtual void turn_right() override
    {
        cout << "car turns right" << endl;
    }

    virtual void apply_brakes() override
    {
        cout << "car applies brakes" << endl;
    }

    Brake brakes[4];
    Engine engine;
    Direction heading;
    int speed;
};

#endif /* CAR_H_ */
