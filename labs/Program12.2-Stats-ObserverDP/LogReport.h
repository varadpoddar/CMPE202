#ifndef LOGREPORT_H_
#define LOGREPORT_H_

#include <iostream>
#include <iomanip>
#include <string>
#include "Observer.h"
#include "BaseballReporter.h"

using namespace std;

class LogReport : public Observer
{
public:
    LogReport(BaseballReporter * const r) : reporter(r), count(0)
    {
        r->attach(this);

        cout << "GAME HITS LOG" << endl;
        cout << endl;
    }

    void update(const string name, const int outs) override;

private:
    BaseballReporter *reporter;
    int count;
};

#endif /* LOGREPORT_H_ */
