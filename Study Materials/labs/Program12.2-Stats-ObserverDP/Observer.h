#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>

using namespace std;

class Observer
{
public:
    virtual ~Observer() {}

    virtual void update(const string name, const int outs) = 0;
};

#endif /* OBSERVER_H_ */
