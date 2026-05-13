#ifndef BASEBALLREPORTER_H_
#define BASEBALLREPORTER_H_

#include "EventMaker.h"
#include "LogReport.h"
#include "GraphReport.h"
#include "TableReport.h"

class BaseballReporter
{
public:
    void distribute_content();

private:
    EventMaker event_maker;

    LogReport   log_report;
    GraphReport graph_report;
    TableReport table_report;
};

#endif /* BASEBALLREPORTER_H_ */
