#include <iostream>
#include "CircularBuffer.h"

using namespace std;

const int SIZE = 5;

int main()
{
    CircularBuffer buffer(SIZE);

    for (int value = 10; value < 100; value+=10)
    {
        if (buffer.get_count() < SIZE)
        {
            buffer.add(value);
            cout << "added " << value << endl;
        }
    }

    for (int i = 1; i < 10; i++)
    {
        if (buffer.get_count() > 0)
        {
            int value = buffer.remove();
            cout << "removed " << value << endl;
        }
    }

    buffer.remove();

    return 0;
}
