#ifndef GRAPHREPORT_H_
#define GRAPHREPORT_H_

#include <string>
#include "Observer.h"
#include "BaseballReporter.h"

using namespace std;

class GraphReport : public Observer
{
public:
    GraphReport(BaseballReporter * const r) : reporter(r)
    {
        r->attach(this);
        singles = doubles = triples = homers = 0;
    }

    void update(const string name, const int outs) override;

private:
    BaseballReporter *reporter;
    int singles, doubles, triples, homers;

    void print_report();
    void print_bar(const char ch, const int count);
};

#endif /* GRAPHREPORT_H_ */
