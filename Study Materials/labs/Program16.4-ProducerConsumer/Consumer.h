#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <queue>
#include <thread>
#include <atomic>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>

#include "ProducerConsumer.h"
#include "SharedQueue.h"

using namespace std;

class Producer;

class Consumer : public ProducerConsumer
{
public:
    Consumer(const int consumers_count, const int consumer_rate,
             SharedQueue& sq);
    ~Consumer();

    int get_count() const override { return consumer_count; }

    int get_active_count() const override
    {
        return active_consumers_count.load();
    }

    condition_variable& get_cv() override { return consumer_cv; }

    void set_producer(Producer * const prod)
    {
        producer = prod;
    }

    void start() override;

    void consume(const int thread_id);

private:
    int consumer_count;
    int consumer_rate;

    SharedQueue& shared_queue;
    Producer *producer;

    thread *threads;
    condition_variable consumer_cv;

    atomic<int> active_consumers_count;

    void print_spaces(const int thread_id) const;
};

#endif /* CONSUMER_H_ */
