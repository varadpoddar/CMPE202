#ifndef SOUND_H_
#define SOUND_H_

#include <string>

using namespace std;

class Engine
{
public:
    string sound() const { return "RRrr RRrr"; }
};

class ChooChoo
{
public:
    string sound() const { return "choo choo"; }
};

#endif /* SOUND_H_ */
