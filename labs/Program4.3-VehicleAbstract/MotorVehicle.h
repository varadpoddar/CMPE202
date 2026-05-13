#ifndef MOTORVEHICLE_H_
#define MOTORVEHICLE_H_

#include <iostream>

using namespace std;

typedef int Brake;
typedef int Direction;
typedef int Engine;

class MotorVehicle
{
public:
    virtual ~MotorVehicle() {}

    virtual void start_engine() = 0;
    virtual void stop_engine() = 0;

    virtual void accelerate()
    {
        cout << "vehicle accelerates" << endl;
    }

    virtual void turn_left()
    {
        cout << "vehicle turns left" << endl;
    }

    virtual void turn_right()
    {
        cout << "vehicle turns right" << endl;
    }

    virtual void apply_brakes()
    {
        cout << "vehicle applies brakes" << endl;
    }

    virtual void drive()
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
    Brake brakes[4];
    Engine engine;
    Direction heading;
    int speed;
};

#endif /* MOTORVEHICLE_H */
