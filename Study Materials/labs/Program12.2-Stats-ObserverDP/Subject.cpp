#include <string>
#include <vector>
#include "Observer.h"
#include "Subject.h"

using namespace std;

void Subject::attach(Observer * const observer)
{
    observers.push_back(observer);
}

void Subject::detach(Observer * const observer)
{
    for (int i = 0; i < observers.size(); i++)
    {
        if (observers[i] == observer)
        {
            observers.erase(observers.begin() + i);
            return;
        }
    }
}

void Subject::notify(const string name, const int outs) const
{
    for (Observer *obs : observers) obs->update(name, outs);
}
