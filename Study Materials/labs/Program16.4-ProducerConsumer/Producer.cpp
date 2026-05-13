#include <iostream>
#include <thread>
#include <atomic>
#include <shared_mutex>
#include <condition_variable>

#include "Producer.h"
#include "Consumer.h"

using namespace std;

Producer::Producer(const int pc, int times, int rate,
                   SharedQueue& sq)
    : producer_count(pc), producer_times(times), producer_rate(rate),
      shared_queue(sq), consumer(nullptr)
{
    threads = new thread[producer_count];

    active_producers_count.store(producer_count);
    data_value.store(0);
}

Producer::~Producer()
{
    for (int i = 0; i < producer_count; i++)
    {
        threads[i].join();
    }

    delete[] threads;
}

void Producer::print_spaces(const int thread_id) const
{
    for (int i = 1; i < thread_id; i++) cout << "              ";
}

void Producer::start()
{
    for (int i = 0; i < producer_count; i++)
    {
        threads[i] = thread(&Producer::produce, this, i + 1);
    }
}

void Producer::produce(const int thread_id)
{
    condition_variable& consumer_cv = consumer->get_cv();

    for (int i = 0; i < producer_times; i++)
    {
        this_thread::sleep_for(
                            chrono::seconds(rand()%producer_rate));

        {
            unique_lock<mutex> queue_lock(shared_queue.get_mutex());
            {
                while (shared_queue.is_full())
                {
                    producer_cv.wait(queue_lock);
                }

                ++data_value;
                shared_queue.enter(data_value.load());

                print_spaces(thread_id);
                printf("%4d", data_value.load());
                shared_queue.print();

                if (shared_queue.just_became_not_empty())
                {
                    consumer_cv.notify_all();
                }
            }
        }
    }

    --active_producers_count;

    print_spaces(thread_id);
    printf("   Done!\n");

    if (active_producers_count.load() == 0)
    {
        consumer_cv.notify_all();
    }
}

