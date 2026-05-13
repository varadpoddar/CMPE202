#ifndef SUMMATION_H_
#define SUMMATION_H_

class Summation
{
public:
    /**
     * Constructor.
     * @param factor the factor of the sequence.
     */
    Summation() : sum(0) {}

    /**
     * Overloaded function call operator.
     * @param amount the amount to add.
     * @return the current sum.
     */
    int operator ()(int amount)
    {
        sum += amount;
        return sum;
    }

private:
    int sum;
};

#endif /* SUMMATION_H_ */
