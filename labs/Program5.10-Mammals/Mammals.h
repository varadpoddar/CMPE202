#ifndef MAMMALS_H_
#define MAMMALS_H_

#include <iostream>
#include "Mammal.h"

using namespace std;

class Human : public Mammal
{
public:
    Human(const double w, const double h, const bool ng)
        : Mammal(w, h), needs_glasses(ng) {};

    ~Human() {};

    void eat()     { cout << "eat with knife and fork" << endl; }
    void perform() { read_book(); sleep(); }

private:
    bool needs_glasses;

    void read_book()
    {
        if (needs_glasses) cout << "squint" << endl;
        cout << "turn pages" << endl;
    }
};

class Cat : public Mammal
{
public:
    Cat(const double w, const double h, const double ff)
        : Mammal(w, h), fur_factor(ff) {};

    ~Cat() {}

    void eat()     { cout << "eat from a bowl" << endl; }
    void perform() { shed(); }

private:
    double fur_factor;

    void shed()
    {
        cout << "shed ";
        if (fur_factor > 1.0) cout << "a lot";
        else                  cout << "a little";
        cout << endl;
    }
};

#endif /* MAMMALS_H_ */
