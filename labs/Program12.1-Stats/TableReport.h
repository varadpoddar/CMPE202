#ifndef TABLEREPORT_H_
#define TABLEREPORT_H_

#include <string>
#include <map>
#include "EventMaker.h"

using namespace std;

class TableReport
{
public:
    void receive_event(const Event * const event, const int outs);

private:
    map<string, int *> hit_map;

    void print_report();
};

#endif /* TABLEREPORT_H_ */
