#ifndef MOTORVEHICLEINTERFACE_H_
#define MOTORVEHICLEINTERFACE_H_

typedef int Brake;
typedef int Direction;
typedef int Engine;

class MotorVehicleInterface
{
public:
    virtual void start_engine() = 0;
    virtual void stop_engine() = 0;
    virtual void accelerate() = 0;
    virtual void turn_left() = 0;
    virtual void turn_right() = 0;
    virtual void apply_brakes() = 0;

    virtual void drive() = 0;
};

#endif /* MOTORVEHICLEINTERFACE_H */
