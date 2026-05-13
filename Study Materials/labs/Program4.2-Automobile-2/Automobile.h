#ifndef AUTOMOBILE_H_
#define AUTOMOBILE_H_

#include <vector>

using namespace std;

typedef int Brake;
typedef int CarWax;
typedef int Direction;
typedef int Engine;
typedef int Headlight;
typedef int Oil;
typedef int Soap;
typedef int Tire;
typedef int Vacuum;

class Automobile
{
public:
    void accelerate();
    void apply_brakes();
    void shut_off_engine();
    void start_engine();
    void turn_left();
    void turn_right();

private:
    Brake brakes[4];
    Direction heading;
    Headlight headlights[4];
    int speed;
    Tire tires[4];
};

class Garage
{
public:
    Garage(Automobile *c) : car(c) {}

    void adjust_headlights();
    void change_oil();
    void change_tires();
    void check_brakes();
    void check_tires();
    void rotate_tires();
    void tuneup_engine();

private:
    Automobile *car;

    Oil new_oil;
    vector<Tire> new_tires;
};

class CarWash
{
public:
    CarWash(Automobile *c) : car(c) {}

    void vacuum_car();
    void wash_car();
    void wax_car();

private:
    Automobile *car;

    Soap soap;
    Vacuum vacuum_cleaner;
    CarWax wax;
};

#endif /* AUTOMOBILE_H_ */
