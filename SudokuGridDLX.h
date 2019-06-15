#ifndef SUDOKUGRIDDLX_H
#define SUDOKUGRIDDLX_H

class SudokuGridDLX
{

    public:
        const static int boardSize;
        const static int boxSideSize;
        const static int sudokuRuleCount;
        void initializeExactCoverGrid(int** sudokuGrid); 
        void addActualSudokuValuesToCoverGrid(int** actualSudokuValuesGrid, int** exactCoverGrid);
    
    private:
        void addExactCoverRuleValues(int** sudokuGrid);
        void addCellRuleValues(int** sudokuGrid);
        void addRowRuleValues(int** sudokuGrid);
        void addColumnRuleValues(int** sudokuGrid);
        void addBoxRuleValues(int** sudokuGrid);
        int getGridRow(int row, int column, int number); 
};

#endif // SUDOKUGRIDDLX_H