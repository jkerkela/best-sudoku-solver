#ifndef SUDOKUGRIDSOLVER_H
#define SUDOKUGRIDSOLVER_H
using namespace std;

class SudokuGridSolver
{
    public:
        void solve(int** sudokuGrid); 
    
    private:
        void solveByDancingLinks(int** sudokuGrid);
        ColumnNode selectColumnNodeHeuristic();
        void search(int k);
};

#endif // SUDOKUGRIDSOLVER_H