#ifndef PRODUCERCONSUMER_H_
#define PRODUCERCONSUMER_H_

#include <condition_variable>

using namespace std;

class ProducerConsumer
{
public:
    virtual ~ProducerConsumer() {}

    virtual int get_count()        const = 0;
    virtual int get_active_count() const = 0;
    virtual condition_variable& get_cv() = 0;

    virtual void start() = 0;
};

#endif /* PRODUCERCONSUMER_H_ */
