#ifndef LOGREPORT_H_
#define LOGREPORT_H_

#include <iostream>
#include <iomanip>
#include "EventMaker.h"

using namespace std;

class LogReport
{
public:
    LogReport() : count(0)
    {
        cout << "GAME HITS LOG" << endl;
        cout << endl;
    }

    void log_event(const Event * const event, const int outs);

private:
    int count;
};

#endif /* LOGREPORT_H_ */
