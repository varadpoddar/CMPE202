#include <iostream>
#include "CircularBuffer.h"

using namespace std;

const int SIZE = 5;

int main()
{
    CircularBuffer cb(SIZE);

    for (int value = 10; value <= 50; value+=10)
    {
        cb.add(value);
    }
    cout << cb << endl;

    cout << "Remove " << cb.remove() << endl;
    cout << "Remove " << cb.remove() << endl;
    cout << cb << endl;

    return 0;
}
