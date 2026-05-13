#ifndef AUTOMOBILEAPP_H_
#define AUTOMOBILEAPP_H_

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

class AutomobileApp
{
public:
    void accelerate();
    void adjust_headlights();
    void apply_brakes();
    void change_oil();
    void change_tires();
    void check_brakes();
    void check_tires();
    void rotate_tires();
    void shut_off_engine();
    void start_engine();
    void tuneup_engine();
    void turn_left();
    void turn_right();
    void vacuum_car();
    void wash_car();
    void wax_car();

private:
    Brake brakes[4];
    Engine engine;
    Oil engine_oil;
    Direction heading;
    Headlight headlights[4];
    int speed;
    Soap soap;
    Tire tires[4];
    Vacuum vacuum_cleaner;
    CarWax wax;
};

#endif /* AUTOMOBILEAPP_H_ */
