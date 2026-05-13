#include "BaseballReporter.h"
#include "EventMaker.h"
#include "LogReport.h"
#include "GraphReport.h"
#include "TableReport.h"

void BaseballReporter::distribute_content()
{
    Event *event = event_maker.next_event();

    while (event != nullptr)
    {
        int outs = event_maker.get_outs();

        log_report.log_event(event, outs);
        graph_report.handle_event(event, outs);
        table_report.receive_event(event, outs);

        delete event;
        event = event_maker.next_event();
    }
}
