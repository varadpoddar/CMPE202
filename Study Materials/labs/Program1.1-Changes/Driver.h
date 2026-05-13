#ifndef DRIVER_H_
#define DRIVER_H_

#include "Car.h"

class Driver
{
public:
    Driver(Car& c) : car(c) {}

    void start_car()
    {
        car.step_on_brake();
        car.insert_key();
        car.turn_key();
        car.step_on_accelerator();
    }

private:
    Car car;
};

#endif /* DRIVER_H_ */
