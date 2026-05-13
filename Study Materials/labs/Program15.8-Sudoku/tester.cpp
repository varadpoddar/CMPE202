#include <iostream>
#include "Sudoku.h"

using namespace std;

int main(int argc, char *argv[])
{
    Sudoku sudoku(argv[1]);

    cout << "Input:" << endl << endl;
    sudoku.print();

    bool solved = sudoku.solve();

    if (solved)
    {
        cout << endl << "Solution:" << endl << endl;
        sudoku.print();
    }
    else
    {
        cout << endl << "No solution" << endl;
    }

    return 0;
}
