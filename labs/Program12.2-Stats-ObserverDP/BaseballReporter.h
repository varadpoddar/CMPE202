#ifndef BASEBALLREPORTER_H_
#define BASEBALLREPORTER_H_

#include "Subject.h"
#include "EventMaker.h"

class BaseballReporter : public Subject
{
public:
    void distribute_content();

    Event *get_current_event() const { return current_event; }

private:
    EventMaker event_maker;
    Event *current_event;
};

#endif /* BASEBALLREPORTER_H_ */
