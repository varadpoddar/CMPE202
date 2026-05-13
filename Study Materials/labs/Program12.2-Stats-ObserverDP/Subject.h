#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>
#include <string>
#include "Observer.h"

using namespace std;

class Subject
{
public:
    void attach(Observer * const observer);
    void detach(Observer * const observer);
    void notify(const string name, const int outs) const;

private:
    vector<Observer *> observers;
};

#endif /* SUBJECT_H_ */
