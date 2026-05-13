#include "MotorVehicleInterface.h"
#include "Car.h"
#include "Truck.h"

int main()
{
    MotorVehicleInterface *mv;

    mv = new Car();
    mv->drive();

    mv = new Truck();
    mv->drive();

    return 0;
}
