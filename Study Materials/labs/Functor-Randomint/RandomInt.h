#ifndef RANDOMINT_H_
#define RANDOMINT_H_

#include <ctime>
using namespace std;

class RandomInt
{
public:
    /**
     * Constructor.
     * @param min the minimum random value.
     * @param max the maximum random value.
     */
    RandomInt(int min, int max) : min(min), max(max)
    {
        srand(time(NULL));  // seed the random number generator
    }

    /**
     * Overloaded function call operator.
     * @return a pseudo-random integer in the range [min, max].
     */
    int operator ()()
    {
        return min + rand()%(max - min + 1);
    }

private:
    int min, max;
};

#endif /* RANDOMINT_H_ */
