#include <iostream>
#include <cassert>
#include "CircularBuffer.h"

using namespace std;

CircularBuffer::CircularBuffer(const int cap)
    : capacity(cap), head(0), tail(0), count(0)
{
    reserve(capacity);
    for (int i = 0; i < capacity; i++) push_back(0);
}

void CircularBuffer::add(const int value)
{
    assert(count < capacity);  // not full

    at(tail) = value;
    tail = (tail + 1)%capacity;
    count++;
}

int CircularBuffer::remove()
{
    assert(count > 0);  // not empty

    int value = at(head);
    head = (head + 1)%capacity;
    count--;

    return value;
}

ostream& operator <<(ostream& ostr, CircularBuffer& buffer)
{
    int i = buffer.head;
    int c = buffer.count;

    cout << "Contents: ";

    while (c > 0)
    {
        cout << buffer.at(i) << " ";
        i = (i + 1)%buffer.capacity;
        c--;
    }

    return ostr;
}
