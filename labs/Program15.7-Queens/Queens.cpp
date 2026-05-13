#include <iostream>
#include "Queens.h"

using namespace std;

void Queens::print_solutions()
{
    search_for_solutions(0);
}

/**
 * Recursively search for solutions starting at the current column.
 * @param col the current column.
 */
void Queens::search_for_solutions(const int col)
{
    // Check each square of the current column.
    for (int row = 0; row < SIZE; row++)
    {
        if (is_safe_square(row, col))
        {
            // Occupy this square for now.
            occupied[row][col] = true;

            // Base case: At the rightmost column.
            // Found a solution, so print it.
            if (col == SIZE - 1) print();

            // Recursively search for solutions to the right.
            else search_for_solutions(col + 1);
        }

        // Backtrack: Leave this square to try the next one.
        occupied[row][col] = false;
    }
}

/**
 * Check that a square is safe from attack from the left.
 * @param row the square's row index.
 * @param col the square's column index.
 */
bool Queens::is_safe_square(const int row, const int col) const
{
    int c = col - 1;

    // Attack from the current row?
    while (c >= 0)
    {
        if (occupied[row][c]) return false;
        c--;
    }

    int r = row - 1;
    c = col - 1;

    // Attack from a diagonal?
    while ((r >= 0) && (c >= 0))
    {
        if (occupied[r][c]) return false;
        r--;
        c--;
    }

    r = row + 1;
    c = col - 1;

    // Attack from the other diagonal?
    while ((r < SIZE) && (c >= 0))
    {
        if (occupied[r][c]) return false;
        r++;
        c--;
    }

    return true;
}

void Queens::print()
{
    count++;

    cout << endl << "Solution #" << count << endl << endl;

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            cout << (occupied[row][col] ? "Q " : ". ");
        }
        cout << endl;
    }
}
