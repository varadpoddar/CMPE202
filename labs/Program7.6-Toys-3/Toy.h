#ifndef TOY_H_
#define TOY_H_

#include <iostream>
#include <string>
#include "PlayAction.h"
#include "Sound.h"

using namespace std;

class Toy
{
public:
    Toy(PlayAction * const p, Sound * const s)
        : play_behavior(p), sound_behavior(s) {}

    virtual ~Toy()
    {
        delete play_behavior;
        delete sound_behavior;
    }

    virtual string what() const = 0;

    void set_play(PlayAction * const p) { play_behavior  = p; }
    void set_sound(Sound * const s)     { sound_behavior = s; }

    string play()  const { return play_behavior->play(); }
    string sound() const { return sound_behavior->sound();}

    virtual void print() const
    {
        cout << endl;
        cout << what() << endl;
        cout << "   play: " << play() << endl;
        cout << "  sound: " << sound() << endl;
    }

private:
    PlayAction *play_behavior;
    Sound      *sound_behavior;
};

class ToyCar : public Toy
{
public:
    ToyCar(PlayAction * const p, Sound * const s) : Toy(p, s) {}

    string what() const override { return "TOY CAR"; }
};

class ModelAirplane : public Toy
{
public:
    ModelAirplane(PlayAction * const p, Sound * const s)
        : Toy(p, s) {}

    string what() const override { return "MODEL AIRPLANE"; }

    string power() const {return "wind up";}

     void print() const override
    {
        Toy::print();
        cout << "  power: " << power() << endl;
    }
};

class TrainSet : public Toy
{
public:
    TrainSet(PlayAction * const p, Sound * const s) : Toy(p, s) {}

    string what() const override { return "TRAIN SET"; }

    string setup() const {return "lay down track";}
    string power() const {return "insert batteries";}

    void print() const override
    {
        Toy::print();
        cout << "  setup: " << setup() << endl;
        cout << "  power: " << power() << endl;
    }
};

#endif /* TOY_H_ */
