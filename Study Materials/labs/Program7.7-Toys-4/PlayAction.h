#ifndef PLAYACTION_H_
#define PLAYACTION_H_

#include <string>

using namespace std;

class PlayAction
{
public:
    virtual ~PlayAction() {}

    virtual string play() const = 0;
};

class Fly : public PlayAction
{
public:
    string play() const override { return "fly it"; }
};

class Roll : public PlayAction
{
public:
    string play() const override { return "roll it"; }
};

#endif /* PLAYACTION_H_ */
