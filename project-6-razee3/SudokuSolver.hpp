/*
Abdullah Razee
May 1st, 2023
Project 6
Prof Ligorio
*/

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace Sudoku
{
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
  /*
  The constructor function of a SudokuSolver class initializes a 9x9 puzzle
  grid with all values set to 0, creating a blank slate for the puzzle to be solved later.
  */

  SudokuSolver();

  /*
  This constructor checks if the puzzle is solvable by calling the solvePuzzle() function.
  */

  SudokuSolver(std::string input_file);

  /*
  isPuzzleSolvable() returns true if the puzzle is solvable, false otherwise.
  We suggest you keep track of this when solving the problem at construction,
  rather than solving the puzzle again each time this function is called.
  */

  bool isPuzzleSolvable() const;

  /*
  setSolvable() records the puzzle as being solvable.
  */

  void setSolvable();

  /*
  getPuzzleNumbers() returns the  2D pointer array representing the puzzle
  */

  int **getPuzzleNumbers() const;

  /*
  setPuzzleNumbers(int** puzzle)
  sets the  2D pointer array representing the puzzle to the value of the parameter
  */

  void setPuzzleNumbers(int **puzzle);

  /*
  returnNextEmpty() returns a Location object with the coordinates of the first 0 found in the 2D pointer array,
  meaning that it is an empty square in the sudoku board.
  To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time.
  Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. If there are no empty squares
  the Location object should have row and col values of -1.
  */

  Sudoku::Location returnNextEmpty() const;

  /*
  checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter
  (which can take on values 1-9) can legally be placed at the given location in the 2D array
  without breaking the rules of sudoku. It returns false if placing value at location is not a legal move.
  Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.
  */

  bool checkLegalValue(int value, Sudoku::Location location) const;

  /*
  This function prints the current state of the puzzle to the console in a grid format.
  */

  void display() const;

  /*
  This function uses a backtracking algorithm to
  recursively search for a solution to the Sudoku puzzle.
  */

  bool solvePuzzle();

private:
  int **puzzle_;
  bool issolvable_;
};

#endif