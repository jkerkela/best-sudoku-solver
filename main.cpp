#include <string>
#include "SudokuGridReader.h"
#include "SudokuGridSolver.h"
using namespace std;

int main()
{
    SudokuGridReader sudokuGridReader;
    SudokuGridSolver sudokuGridSolver;
    int** sudokuGrid = sudokuGridReader.getSudokuGrid();
    sudokuGridSolver.solve(sudokuGrid);
}