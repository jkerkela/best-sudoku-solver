#include <array>
#include <iostream>
#include <stdio.h>
#include "SudokuGridDLX.h"
using namespace std;

const int SudokuGridDLX::boardSize = 9;
const int SudokuGridDLX::boxSideSize = 3;
const int SudokuGridDLX::sudokuRuleCount = 4;
int gridColumnPosition = 0;

void SudokuGridDLX::initializeExactCoverGrid(int** sudokuGrid)
{
    cout << "Initializing Exact Cover grid"  << endl;
    SudokuGridDLX::addExactCoverRuleValues(sudokuGrid);

};

void SudokuGridDLX::addActualSudokuValuesToCoverGrid(int** actualSudokuValuesGrid, int** exactCoverGrid)
{
    for(int i = 1; i <= boardSize; i++){
        for(int j = 1; j <= boardSize; j++){
            int sudokuCellValue = actualSudokuValuesGrid[i - 1][j - 1];
            if (sudokuCellValue != 0){ 
                for(int num = 1; num <= boardSize; num++){
                    if (num != sudokuCellValue){
                        int rowToFill = SudokuGridDLX::getGridRow(i, j, num);
                        //ORIG:
                        //Arrays.fill(exactCoverGrid[SudokuGridDLX::getGridRow(i, j, num)], 0);
                        for (int column = 0; column < boardSize * boardSize * sudokuRuleCount; column++) {
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
    for(int row = 1; row <= boardSize; row++){
            for(int column = 1; column <= boardSize; column++, gridColumnPosition++){
                for(int number = 1; number <= boardSize; number++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

int SudokuGridDLX::getGridRow(int row, int column, int number)
{
    return (row - 1) * boardSize * boardSize + 
    (column - 1) * boardSize + (number - 1);
};

void SudokuGridDLX::addRowRuleValues(int** sudokuGrid)
{
    for(int row = 1; row <= boardSize; row++){
            for(int number = 1; number <= boardSize; number++, gridColumnPosition++){
                for(int column = 1; column <= boardSize; column++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

void SudokuGridDLX::addColumnRuleValues(int** sudokuGrid)
{
    for(int column = 1; column <= boardSize; column++){
            for(int number = 1; number <= boardSize; number++, gridColumnPosition++){
                for(int row = 1; row <= boardSize; row++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

void SudokuGridDLX::addBoxRuleValues(int** sudokuGrid)
{
    for(int row = 1; row <= boardSize; row += boxSideSize){
        for(int column = 1; column <= boardSize; column += boxSideSize){
            for(int number = 1; number <= boardSize; number++, gridColumnPosition++){
                for(int boxRowPosition = 0; boxRowPosition < boxSideSize; boxRowPosition++){
                    for(int boxColumnPosition = 0; boxColumnPosition < boxSideSize; boxColumnPosition++){
                        sudokuGrid[SudokuGridDLX::getGridRow(row + boxRowPosition, column + boxColumnPosition, number)][gridColumnPosition] = 1;
                    }
                }
            }
        }
    }
}      