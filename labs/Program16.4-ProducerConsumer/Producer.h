#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <queue>
#include <thread>
#include <atomic>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>

#include "ProducerConsumer.h"
#include "SharedQueue.h"

using namespace std;

class Consumer;

class Producer : public ProducerConsumer
{
public:
    Producer(const int producer_count, int producer_times,
             int producer_rate, SharedQueue& sq);
    ~Producer();

    int get_count() const override { return producer_count; }

    int get_active_count() const override
    {
        return active_producers_count.load();
    }

    condition_variable& get_cv() override { return producer_cv; }

    void set_consumer(Consumer * const cons)
    {
        consumer = cons;
    }

    void start() override;

    void produce(const int thread_id);

private:
    int producer_count;
    int producer_times;
    int producer_rate;

    SharedQueue& shared_queue;
    Consumer *consumer;

    thread *threads;
    condition_variable producer_cv;

    atomic<int> data_value;
    atomic<int> active_producers_count;

    void print_spaces(const int thread_id) const;
};

#endif /* PRODUCER_H_ */
