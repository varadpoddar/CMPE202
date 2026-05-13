#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

class CircularBuffer
{
public:
    CircularBuffer(const int cap);
    ~CircularBuffer() { delete[] buffer; }

    int get_count() const { return count; }

    void add(const int value);
    int remove();

private:
    int capacity;
    int head, tail;
    int count;

    int *buffer;

    bool class_invariant() const;
};

#endif /* CIRCULARBUFFER_H_ */
