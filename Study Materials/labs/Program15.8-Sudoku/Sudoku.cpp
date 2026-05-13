#include <iostream>
#include <fstream>
#include "Sudoku.h"

using namespace std;

Sudoku::Sudoku(const char *file_name)
{
    try
    {
        // Read the given cell values.
        ifstream grid_file(file_name);
        grid_file.exceptions(ifstream::failbit | ifstream::badbit);

        for (int row = 0; row < GRID_SIZE; row++)
        {
            for (int col = 0; col < GRID_SIZE; col++)
            {
                grid_file >> grid[row][col];
            }
        }
    }
    catch (ifstream::failure& ex)
    {
        cerr << "Input file error: " << file_name << endl;
        exit(-1);
    }
}

bool Sudoku::is_number_ok(const int row, const int col,
                          const int number) const
{
    // Check column.
    for (int c = 0; c < GRID_SIZE; c++)
    {
        if (grid[row][c] == number) return false;
    }

    // Check row.
    for (int r = 0; r < GRID_SIZE; r++)
    {
        if (grid[r][col] == number) return false;
    }

    int block_row_start = row - row%BLOCK_SIZE;
    int block_col_start = col - col%BLOCK_SIZE;
    int block_row_end = block_row_start + BLOCK_SIZE;
    int block_col_end = block_col_start + BLOCK_SIZE;

    // Check block.
    for (int r = block_row_start; r < block_row_end; r++)
    {
        for (int c = block_col_start; c < block_col_end; c++)
        {
            if (grid[r][c] == number) return false;
        }
    }

    return true;
}

bool Sudoku::does_solution_exist(int row, int col)
{
    // Base case: At lower right corner.
    if ((row == GRID_SIZE-1) && (col == GRID_SIZE)) return true;

    // Wrap around to the next row.
    if (col == GRID_SIZE)
    {
        row++;
        col = 0;
    }

    // Cell value given?
    if (grid[row][col] != 0)
    {
        return does_solution_exist(row, col + 1);
    }

    // Try each number for the cell.
    for (int number = 1; number <= GRID_SIZE; number++)
    {
        if (is_number_ok(row, col, number))
        {
            grid[row][col] = number;

            // Recursively try the next cell.
            if (does_solution_exist(row, col + 1)) return true;
        }
    }

    // Backtrack: Failed to find a solution with this cell.
    grid[row][col] = 0;

    return false;
}

void Sudoku::print() const
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        if ((row > 0) && (row%BLOCK_SIZE == 0))
        {
            cout << "------+-------+-------" << endl;
        }

        for (int col = 0; col < GRID_SIZE; col++)
        {
            if ((col > 0) && (col%BLOCK_SIZE == 0)) cout << "| ";

            int g = grid[row][col];
            if (g > 0) cout << g << " ";
            else       cout << ". ";
        }

        cout << endl;
    }
}
