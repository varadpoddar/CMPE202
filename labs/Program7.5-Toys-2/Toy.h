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
    virtual ~Toy() {}

    virtual string what()  const = 0;
    virtual string play()  const = 0;
    virtual string sound() const = 0;

    virtual void print() const
    {
        cout << endl;
        cout << what() << endl;
        cout << "   play: " << play() << endl;
        cout << "  sound: " << sound() << endl;
    }
};

class ToyCar : public Toy, public Roll, public Engine
{
public:
    string what()  const override { return "TOY CAR"; }
    string play()  const override { return Roll::play(); }
    string sound() const override { return Engine::sound(); }
};

class ModelAirplane : public Toy, public Fly, public Engine
{
public:
    string what()  const override { return "MODEL AIRPLANE"; }
    string play()  const override { return Fly::play(); }
    string sound() const override { return Engine::sound(); }

    string power() const { return "wind up"; }

    void print() const override
    {
        Toy::print();
        cout << "  power: " << power() << endl;
    }
};

class TrainSet : public Toy, public Roll, public ChooChoo
{
public:
    string what()  const override { return "TRAIN SET"; }
    string play()  const override { return Roll::play(); }
    string sound() const override { return ChooChoo::sound(); }

    string setup() const { return "lay down track"; }
    string power() const { return "insert batteries"; }

    void print() const override
    {
        Toy::print();
        cout << "  setup: " << setup() << endl;
        cout << "  power: " << power() << endl;
    }
};

#endif /* TOY_H_ */
