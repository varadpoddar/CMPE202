#ifndef QUEENS_H_
#define QUEENS_H_

const int SIZE = 8;

class Queens
{
public:
    Queens() : count(0)
    {
        for (int row = 0; row < SIZE; row ++)
        {
            for (int col = 0; col < SIZE; col ++)
            {
                occupied[row][col] = false;
            }
        }
    }

    void print_solutions();

private:
    bool occupied[SIZE][SIZE];
    int count;

    void search_for_solutions(const int col);
    bool is_safe_square(const int row, const int col) const;
    void print();
};

#endif /* QUEENS_H_ */
