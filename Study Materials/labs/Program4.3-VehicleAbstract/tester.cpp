#include "MotorVehicle.h"
#include "Car.h"
#include "Truck.h"

int main()
{
    MotorVehicle *mv;

    mv = new Car();
    mv->drive();

    mv = new Truck();
    mv->drive();

    return 0;
}
