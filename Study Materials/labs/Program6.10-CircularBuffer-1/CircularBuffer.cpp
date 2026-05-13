#include <cassert>
#include "CircularBuffer.h"

/**
 * @invariant (0 <= head < capacity) and (0 <= tail < capacity)
 */
bool CircularBuffer::class_invariant() const
{
    return (0 <= head) && (head < capacity)
        && (0 <= tail) && (tail < capacity);
}

/**
 * Constructor
 * @parm cap the capacity of the buffer.
 * @postcondition the buffer is empty.
 */
CircularBuffer::CircularBuffer(const int cap)
    : capacity(cap), head(0), tail(0), count(0),
      buffer(new int[capacity])
{
    assert(class_invariant());
}

/**
 * Add a new value to the tail of the buffer.
 * @parm value the value to add.
 * @precondition the buffer is not full.
 * @postcondition the buffer is not empty.
 */
void CircularBuffer::add(const int value)
{
    assert(count < capacity);  // not full

    buffer[tail] = value;
    tail = (tail + 1)%capacity;
    count++;

    assert(count > 0);  // not empty
    assert(class_invariant());
}

/**
 * Remove a value from the head of the buffer.
 * @return the removed value.
 * @precondition the buffer is not empty.
 * @postcondition the buffer is not full.
 */
int CircularBuffer::remove()
{
    assert(count > 0);  // not empty

    int value = buffer[head];
    head = (head + 1)%capacity;
    count--;

    assert(count < capacity);  // not full
    assert(class_invariant());

    return value;
}
