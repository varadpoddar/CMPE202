#ifndef MAMMAL_H_
#define MAMMAL_H_

#include <iostream>

using namespace std;

class Mammal
{
public:
    Mammal(const double w, const double h) : weight(w), height(h) {}
    virtual ~Mammal() {}

    virtual void eat() = 0;
    virtual void perform() = 0;

    double get_weight() const { return weight; }
    double get_height() const { return height; }

protected:
    void sleep()
    {
        cout << "close eyes" << endl;
        snore();
    }

private:
    double weight, height;

    void snore()
    {
        cout << "Zzzz" << endl;
    }
};

#endif /* MAMMAL_H_ */
