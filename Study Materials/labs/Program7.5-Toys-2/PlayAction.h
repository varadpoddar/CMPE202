#ifndef PLAYACTION_H_
#define PLAYACTION_H_

#include <string>

using namespace std;

class Fly
{
public:
    string play() const { return "fly it"; }
};

class Roll
{
public:
    string play() const { return "roll it"; }
};

#endif /* PLAYACTION_H_ */
