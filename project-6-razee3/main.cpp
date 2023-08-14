#include "SudokuSolver.hpp"

int main(){
    SudokuSolver puzzle;
    puzzle.display();
    SudokuSolver puzzle1("puzzle1.csv");
    puzzle1.display();
}