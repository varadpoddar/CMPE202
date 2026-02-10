#include <iostream>

// Base case:
// If n == 1, return 1 because 1^2 = 1.
//
// Simpler recursive case:
// n^2 = (n - 1)^2 + (2n - 1), where (2n - 1) is the nth odd number.
// The recursive call computes (n - 1)^2, then we add the nth odd number.
int square_recursive(int n)
{
    if (n == 1)
    {
        return 1;
    }

    return square_recursive(n - 1) + (2 * n - 1);
}

int main()
{
    for (int n = 1; n <= 10; ++n)
    {
        std::cout << n << "^2 = " << square_recursive(n) << '\n';
    }

    return 0;
}
