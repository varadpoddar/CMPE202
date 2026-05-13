#include <iostream>
#include "CircularBuffer.h"

using namespace std;

CircularBuffer::CircularBuffer(const int cap)
    : capacity(cap), head(0), tail(0), count(0)
{
    buffer.reserve(capacity);
    for (int i = 0; i < capacity; i++) buffer.push_back(0);
}

void CircularBuffer::add(const int value)
{
    buffer.at(tail) = value;
    tail = (tail + 1)%capacity;
    count++;
}

int CircularBuffer::remove()
{
    int value = buffer.at(head);
    head = (head + 1)%capacity;
    count--;

    return value;
}

ostream& operator <<(ostream& ostr, CircularBuffer& cb)
{
    int i = cb.head;
    int c = cb.count;

    cout << "Contents: ";

    while (c > 0)
    {
        cout << cb.buffer.at(i) << " ";
        i = (i + 1)%cb.capacity;
        c--;
    }

    return ostr;
}
