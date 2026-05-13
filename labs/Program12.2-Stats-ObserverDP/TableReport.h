#ifndef TABLEREPORT_H_
#define TABLEREPORT_H_

#include <string>
#include <map>
#include "Observer.h"
#include "BaseballReporter.h"

using namespace std;

class TableReport : public Observer
{
public:
    TableReport(BaseballReporter * const r) : reporter(r)
    {
        r->attach(this);
    }

    void update(const string name, const int outs) override;

private:
    BaseballReporter *reporter;
    map<string, int *> hit_map;

    void print_report();
};

#endif /* TABLEREPORT_H_ */
