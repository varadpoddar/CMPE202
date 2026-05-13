// Compute the squares of integers using recursion based on mathematical induction.
// The square of n is computed using the formula: n^2 = (n-1)^2 + (2n - 1)
// where (2n - 1) is the nth odd number.
// This works because the sum of the first n odd numbers equals n^2.

#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Recursive function to compute the square of integer n.
 *
 * Base case: When n == 1, return 1. The square of 1 is simply 1.
 *            This is the stopping condition that prevents infinite recursion.
 *
 * Recursive (simpler) case: When n > 1, compute square(n-1) + (2*n - 1).
 *            The simpler case reduces n by 1, moving closer to the base case.
 *            It adds the nth odd number (2n-1) to the square of (n-1),
 *            which builds up to n^2 since n^2 = (n-1)^2 + 2n - 1.
 */
int square(int n) {
    // Base case: the square of 1 is 1 and stops recursion
    if (n == 1) {
        return 1;
    }

    // Recursive (simpler) case: square(n) = square(n-1) + nth odd number (2n-1)
    return square(n - 1) + (2 * n - 1);
}

int main() {
    cout << setw(5) << "n" << setw(15) << "nth odd" << setw(15) << "n squared" << endl;
    cout << string(35, '-') << endl;

    for (int i = 1; i <= 10; i++) {
        cout << setw(5) << i
             << setw(15) << (2 * i - 1)
             << setw(15) << square(i) << endl;
    }

    return 0;
}

// Example output:
//     n      nth odd      n squared
// -----------------------------------
//     1              1              1
//     2              3              4
//     3              5              9
//     4              7             16
//     5              9             25
//     6             11             36
//     7             13             49
//     8             15             64
//     9             17             81
//    10             19            100
