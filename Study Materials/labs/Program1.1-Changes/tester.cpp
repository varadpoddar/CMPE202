#include "Car.h"
#include "Driver.h"

int main()
{
    Car my_car;
    Driver driver(my_car);

    driver.start_car();
    return 0;
}
