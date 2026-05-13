#ifndef SOUND_H_
#define SOUND_H_

#include <string>

using namespace std;

class Sound
{
public:
    virtual ~Sound() {}

    virtual string sound() const = 0;
};

class ChooChoo : public Sound
{
public:
    string sound() const override { return "choo choo"; }
};

class Engine : public Sound
{
public:
    string sound() const override { return "RRrr RRrr"; }
};

#endif /* SOUND_H_ */
