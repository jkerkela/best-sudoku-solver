#ifndef SUDOKUGRIDSOLVER_H
#define SUDOKUGRIDSOLVER_H
using namespace std;

class SudokuGridSolver
{
    
public:
    void solve(int** sudokuGrid); 

private:
    void solveByDancingLinks(int** sudokuGrid);
};

#endif // SUDOKUGRIDSOLVER_H