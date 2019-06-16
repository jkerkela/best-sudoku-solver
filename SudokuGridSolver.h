#ifndef SUDOKUGRIDSOLVER_H
#define SUDOKUGRIDSOLVER_H
#include "DancingLinks.h"

class SudokuGridSolver
{
    public:
        void solve(int** sudokuGrid); 
    
    private:
        void solveByDancingLinks(int** sudokuGrid);
        ColumnNode selectColumnNodeHeuristic();
        ColumnNode makeDLXBoardWithLinks(int** grid);
        int** initializeArray();
        void search(int k);
};

#endif // SUDOKUGRIDSOLVER_H