#include <iostream>
#include "CircularBuffer.h"

using namespace std;

const int SIZE = 5;

int main()
{
    CircularBuffer buffer(SIZE);

    for (int value = 10; value <= 50; value+=10)
    {
        buffer.add(value);
    }
    cout << buffer << endl;

    buffer.at(1) = 99;  // INVALID!
    cout << buffer << endl;

    cout << "Remove " << buffer.remove() << endl;
    cout << "Remove " << buffer.remove() << endl;
    cout << buffer << endl;

    buffer.erase(buffer.begin() + 1);  // INVALID!
    cout << buffer << endl;

    return 0;
}
