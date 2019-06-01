#ifndef SUDOKUGRIDDLX_H
#define SUDOKUGRIDDLX_H
#include <stdio.h>
using namespace std;

class SudokuGridDLX
{

private:
    void addExactCoverRuleValues(int sudokuGrid[9*9*9][9*9*4]);
    void addCellRuleValues(int sudokuGrid[9*9*9][9*9*4]);
    void addRowRuleValues(int sudokuGrid[9*9*9][9*9*4]);
    void addColumnRuleValues(int sudokuGrid[9*9*9][9*9*4]);
    void addBoxRuleValues(int sudokuGrid[9*9*9][9*9*4]);
    int getGridRow(int row, int column, int number);
   
public:
    const static int boardSize;
    const static int boxSideSize;
    const static int sudokuRuleCount;
    int** initializeExactCoverGrid(); 
    int** addActualSudokuValuesToCoverGrid(int** actualSudokuValuesGrid, int** exactCoverGrid);
    
};

#endif // SUDOKUGRIDDLX_H