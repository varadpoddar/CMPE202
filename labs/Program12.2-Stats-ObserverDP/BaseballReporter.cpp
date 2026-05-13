#include "BaseballReporter.h"
#include "EventMaker.h"

void BaseballReporter::distribute_content()
{
    do
    {
        current_event = event_maker.next_event();

        if (current_event != nullptr)
        {
            notify(current_event->get_name(),
                   event_maker.get_outs());
            delete current_event;
        }
    } while (current_event != nullptr);
}
