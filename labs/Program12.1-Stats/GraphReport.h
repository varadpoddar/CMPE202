#ifndef GRAPHREPORT_H_
#define GRAPHREPORT_H_

#include "EventMaker.h"

class GraphReport
{
public:
    GraphReport()
    {
        singles = doubles = triples = homers = 0;
    }

    void handle_event(const Event * const event, const int outs);

private:
    int singles, doubles, triples, homers;

    void print_report() const;
    void print_bar(const char ch, const int count) const;
};

#endif /* GRAPHREPORT_H_ */
