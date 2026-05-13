#ifndef EXECUTIVEPASS_H_
#define EXECUTIVEPASS_H_

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class ExecutivePass
{
public:
    // Constructor
    ExecutivePass() : key(generate_key()) {}

    // Copy constructor
    ExecutivePass(ExecutivePass& other)
        : key(generate_key()), holder(other.holder) {}

    // Copy assignment operator
    ExecutivePass& operator =(ExecutivePass& other)
    {
        if (this != &other)
        {
            holder = other.holder;
            key = generate_key();
        }

        return *this;
    }

    void obtain(const string hldr) { holder = hldr; }

    void print()
    {
        cout << "Executive pass now held by " << holder
             << ", key = " << key << endl;
    }

private:
    int key;
    string holder;

    int generate_key() const { return rand()%10000 + 1000; }
};

#endif /* EXECUTIVEPASS_H_ */
