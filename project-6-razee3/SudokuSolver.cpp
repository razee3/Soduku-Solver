/*
Abdullah Razee
May 1st, 2023
Project 6
Prof Ligorio
*/

#include "SudokuSolver.hpp"

/*
The constructor function of a SudokuSolver class initializes a 9x9 puzzle
grid with all values set to 0, creating a blank slate for the puzzle to be solved later.
*/

SudokuSolver::SudokuSolver() : issolvable_(false)
{
    puzzle_ = new int *[9];
    for (int i = 0; i < 9; i++)
    {
        puzzle_[i] = new int[9]{0};
    }
}

/*
This constructor checks if the puzzle is solvable by calling the solvePuzzle() function.
*/

SudokuSolver::SudokuSolver(std::string input_file)
{

    puzzle_ = new int *[9];
    int i = 0;
    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        puzzle_[i] = new int[9];
    }
    std::ifstream inputfile(input_file);
    std::string line;
    while (std::getline(inputfile, line))
    {
        std::string number;
        std::stringstream ss(line);
        while (std::getline(ss, number, ','))
        {
            puzzle_[i][j] = stoi(number);
            j++;
            if (j == 9)
            {
                i++;
                j = 0;
            }
        }
    }

    if (solvePuzzle() == false)
    {
        issolvable_ = false;
    }
}

/*
isPuzzleSolvable() returns true if the puzzle is solvable, false otherwise.
We suggest you keep track of this when solving the problem at construction,
rather than solving the puzzle again each time this function is called.
*/

bool SudokuSolver::isPuzzleSolvable() const
{
    return issolvable_;
}

/*
setSolvable() records the puzzle as being solvable.
*/

void SudokuSolver::setSolvable()
{
    issolvable_ = true;
}

/*
getPuzzleNumbers() returns the  2D pointer array representing the puzzle
*/

int **SudokuSolver::getPuzzleNumbers() const
{
    return puzzle_;
}

/*
setPuzzleNumbers(int** puzzle)
sets the  2D pointer array representing the puzzle to the value of the parameter
*/

void SudokuSolver::setPuzzleNumbers(int **puzzle)
{
    puzzle_ = puzzle;
}

/*
returnNextEmpty() returns a Location object with the coordinates of the first 0 found in the 2D pointer array,
meaning that it is an empty square in the sudoku board.
To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time.
Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. If there are no empty squares
the Location object should have row and col values of -1.
*/

Sudoku::Location SudokuSolver::returnNextEmpty() const
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (puzzle_[row][col] == 0)
            {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

/*
checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter
(which can take on values 1-9) can legally be placed at the given location in the 2D array
without breaking the rules of sudoku. It returns false if placing value at location is not a legal move.
Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.
*/

bool SudokuSolver::checkLegalValue(int value, Sudoku::Location position) const
{

    int row = position.row;
    int col = position.col;
    int begin_row = row - row % 3;
    int begin_column = col - col % 3;

    for (int i = 0; i < 9; i++)
    {
        if (puzzle_[i][col] == value || puzzle_[row][i] == value)
        {
            return false;
        }
    }

    for (int i = begin_row; i < begin_row + 3; i++)
    {
        for (int j = begin_column; j < begin_column + 3; j++)
        {
            if (puzzle_[i][j] == value && (i != row || j != col))
            {
                return false;
            }
        }
    }

    return true;
}

/*
This function prints the current state of the puzzle to the console in a grid format.
*/

void SudokuSolver::display() const
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)

        {

            if (puzzle_[row][col] == 0)
            {
                if (col == 2 || col == 5)
                    std::cout << "X"
                              << "  | ";
                else if (col == 8)
                    std::cout << "X" << std::endl;
                else
                    std::cout << "X"
                              << " ";
            }
            else
            {
                if (col == 2 || col == 5)
                {
                    std::cout << puzzle_[row][col] << "  | ";
                }
                else if (col == 8)
                {
                    std::cout << puzzle_[row][col] << std::endl;
                }
                else
                {
                    std::cout << puzzle_[row][col] << " ";
                }
            }
        }

        if (row == 2 || row == 5)
        {

            std::cout << "- - - - - - - - - - - - " << std::endl;
        }
    }
}

/*
This function uses a backtracking algorithm to
recursively search for a solution to the Sudoku puzzle.
*/

bool SudokuSolver::solvePuzzle()
{
    Sudoku::Location position = returnNextEmpty();
    if (position.row == -1 && position.col == -1)
    {
        issolvable_ = true;
        return true;
    }
    for (int i = 1; i <= 9; i++)
    {
        if (checkLegalValue(i, position))
        {
            puzzle_[position.row][position.col] = i;
            if (solvePuzzle())
            {
                issolvable_ = true;
                return true;
            }
            puzzle_[position.row][position.col] = 0;
        }
    }
    return false;
}