#include <string>
#include "iohandlers/SudokuGridReader.h"
#include "SudokuGridSolver.h"

int main() {
    SudokuGridReader sudokuGridReader;
    SudokuGridSolver sudokuGridSolver;
    int** sudokuGrid = sudokuGridReader.getSudokuGrid();
    sudokuGridSolver.solve(sudokuGrid);
}