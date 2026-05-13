#include "Toy.h"

int main()
{
    Toy *car   = new ToyCar(new Roll(), new Engine());
    Toy *plane = new ModelAirplane(new Fly(), new Engine());
    Toy *train = new TrainSet(new Roll(), new ChooChoo());

    car->print();
    plane->print();
    train->print();

    train->set_sound(new Engine());
    train->print();

    delete car;
    delete plane;
    delete train;

    return 0;
}
