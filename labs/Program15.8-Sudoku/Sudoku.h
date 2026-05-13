#ifndef SUDOKU_H_
#define SUDOKU_H_

class Sudoku
{
public:
    Sudoku(const char *file_name);

    bool solve() { return does_solution_exist(0, 0); }

    void print() const;

private:
    static const int BLOCK_SIZE = 3;
    static const int GRID_SIZE  = BLOCK_SIZE*BLOCK_SIZE;

    int grid[GRID_SIZE][GRID_SIZE];

    bool is_number_ok(const int row, const int col,
                      const int number) const;
    bool does_solution_exist(int row, int col);
};

#endif /* SUDOKU_H_ */
