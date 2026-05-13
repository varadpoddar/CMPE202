#include <iostream>
#include <thread>
#include <atomic>
#include <shared_mutex>
#include <condition_variable>

#include "Producer.h"
#include "Consumer.h"

using namespace std;

Consumer::Consumer(const int cc, int rate, SharedQueue& sq)
    : consumer_count(cc), consumer_rate(rate),
      shared_queue(sq), producer(nullptr)

{
    threads = new thread[consumer_count];

    active_consumers_count.store(consumer_count);
}

Consumer::~Consumer()
{
    for (int i = 0; i < consumer_count; i++)
    {
        threads[i].join();
    }

    delete[] threads;
}

void Consumer::print_spaces(const int thread_id) const
{
    int k = producer->get_count() + thread_id;
    for (int i = 1; i < k; i++) cout << "              ";
}

void Consumer::start()
{
    for (int i = 0; i < consumer_count; i++)
    {
        threads[i] = thread(&Consumer::consume, this, i + 1);
    }
}

void Consumer::consume(const int thread_id)
{
    condition_variable& producer_cv = producer->get_cv();

    while (true)
    {
        this_thread::sleep_for(
                            chrono::seconds(rand()%consumer_rate));

        {
            unique_lock<mutex> queue_lock(shared_queue.get_mutex());
            {
                while (   shared_queue.is_empty()
                       && (producer->get_active_count() > 0))
                {
                    consumer_cv.wait(queue_lock);
                }

                if (shared_queue.is_empty()) break;

                int value = shared_queue.remove();

                print_spaces(thread_id);
                printf("%4d", -value);
                shared_queue.print();

                if (shared_queue.just_became_not_full())
                {
                    producer_cv.notify_all();
                }
            }
        }
    }

    --active_consumers_count;

    print_spaces(thread_id);
    printf("   Done!\n");
}
