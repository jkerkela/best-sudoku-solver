#include "SudokuGridDLX.h"
#include "Constants.h"

#include <array>
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

int gridColumnPosition = 0;

void SudokuGridDLX::initializeExactCoverGrid(int** sudokuGrid)
{
    cout << "Initializing Exact Cover grid"  << endl;
    SudokuGridDLX::addExactCoverRuleValues(sudokuGrid);

};

void SudokuGridDLX::addActualSudokuValuesToCoverGrid(int** actualSudokuValuesGrid, int** exactCoverGrid)
{
    for(int i = 1; i <= sudokuBoardSize; i++){
        for(int j = 1; j <= sudokuBoardSize; j++){
            int sudokuCellValue = actualSudokuValuesGrid[i - 1][j - 1];
            if (sudokuCellValue != 0){ 
                for(int num = 1; num <= sudokuBoardSize; num++){
                    if (num != sudokuCellValue){
                        int rowToFill = SudokuGridDLX::getGridRow(i, j, num);
                        for (int column = 0; column < sudokuBoardSize * sudokuBoardSize * sudokuRuleCount; column++) {
                            exactCoverGrid[rowToFill][column] = 0;
                        }
                    }
                }
            }
        }
    }
}

void SudokuGridDLX::addExactCoverRuleValues(int** sudokuGrid)
{
    SudokuGridDLX::addCellRuleValues(sudokuGrid);
    SudokuGridDLX::addRowRuleValues(sudokuGrid);
    SudokuGridDLX::addColumnRuleValues(sudokuGrid);
    SudokuGridDLX::addBoxRuleValues(sudokuGrid);
};

void SudokuGridDLX::addCellRuleValues(int** sudokuGrid)
{
    for(int row = 1; row <= sudokuBoardSize; row++){
            for(int column = 1; column <= sudokuBoardSize; column++, gridColumnPosition++){
                for(int number = 1; number <= sudokuBoardSize; number++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

int SudokuGridDLX::getGridRow(int row, int column, int number)
{
    return (row - 1) * sudokuBoardSize * sudokuBoardSize + 
    (column - 1) * sudokuBoardSize + (number - 1);
};

void SudokuGridDLX::addRowRuleValues(int** sudokuGrid)
{
    for(int row = 1; row <= sudokuBoardSize; row++){
            for(int number = 1; number <= sudokuBoardSize; number++, gridColumnPosition++){
                for(int column = 1; column <= sudokuBoardSize; column++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

void SudokuGridDLX::addColumnRuleValues(int** sudokuGrid)
{
    for(int column = 1; column <= sudokuBoardSize; column++){
            for(int number = 1; number <= sudokuBoardSize; number++, gridColumnPosition++){
                for(int row = 1; row <= sudokuBoardSize; row++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

void SudokuGridDLX::addBoxRuleValues(int** sudokuGrid)
{
    for(int row = 1; row <= sudokuBoardSize; row += sudokuBoxSideSize){
        for(int column = 1; column <= sudokuBoardSize; column += sudokuBoxSideSize){
            for(int number = 1; number <= sudokuBoardSize; number++, gridColumnPosition++){
                for(int sudokuBoxRowPosition = 0; sudokuBoxRowPosition < sudokuBoxSideSize; sudokuBoxRowPosition++){
                    for(int sudokuBoxColumnPosition = 0; sudokuBoxColumnPosition < sudokuBoxSideSize; sudokuBoxColumnPosition++){
                        sudokuGrid[SudokuGridDLX::getGridRow(row + sudokuBoxRowPosition, column + sudokuBoxColumnPosition, number)][gridColumnPosition] = 1;
                    }
                }
            }
        }
    }
}      