#include <iostream>
#include <time.h>

#include "SharedQueue.h"
#include "Producer.h"
#include "Consumer.h"

using namespace std;

int main()
{
    const int QUEUE_CAPACITY = 8;

    const int PRODUCER_COUNT = 2;
    const int PRODUCER_TIMES = 5;
    const int PRODUCER_RATE  = 3;

    const int CONSUMER_COUNT = 3;
    const int CONSUMER_RATE  = 5;

    for (int i = 1; i <= PRODUCER_COUNT; i++)
    {
        cout << "Producer #" << i << "   ";
    }
    for (int i = 1; i <= CONSUMER_COUNT; i++)
    {
        cout << "Consumer #" << i << "   ";
    }
    cout << endl;

    srand(time(0));

    SharedQueue shared_queue(QUEUE_CAPACITY);

    Producer producer(PRODUCER_COUNT, PRODUCER_TIMES,
                      PRODUCER_RATE, shared_queue);
    Consumer consumer(CONSUMER_COUNT, CONSUMER_RATE,
                      shared_queue);

    producer.set_consumer(&consumer);
    consumer.set_producer(&producer);

    producer.start();
    consumer.start();

    return 0;
}
