#include <iostream>
#include <stdio.h>
#include "SudokuGridDLX.h"
using namespace std;

const int SudokuGridDLX::boardSize = 9;
const int SudokuGridDLX::boxSideSize = 3;
const int SudokuGridDLX::sudokuRuleCount = 4;
int gridColumnPosition = 0;

int** SudokuGridDLX::initializeExactCoverGrid()
{
    cout << "Initializing Exact Cover grid"  << endl;
    int sudokuGrid[boardSize * boardSize * boardSize][boardSize * boardSize * sudokuRuleCount]
    SudokuGridDLX::addExactCoverRuleValues(sudokuGrid);
};

int** addActualSudokuValuesToCoverGrid(int** actualSudokuValuesGrid, int** exactCoverGrid)
{
    //TODO: implemente
    for(int i = 1; i <= S; i++){
        for(int j = 1; j <= S; j++){
            int sudokuCellValue = actualSudokuValuesGrid[i - 1][j - 1];
            if (sudokuCellValue != 0){ 
                for(int num = 1; num <= S; num++){
                    if (num != sudokuCellValue){
                        Arrays.fill(exactCoverGrid[getIdx(i, j, num)], 0);
                    }
                }
            }
        }
    }
}
void SudokuGridDLX::addExactCoverRuleValues(int sudokuGrid[9*9*9][9*9*4])
{
    SudokuGridDLX::addCellRuleValues(sudokuGrid);
    SudokuGridDLX::addRowRuleValues(sudokuGrid);
    SudokuGridDLX::addColumnRuleValues(sudokuGrid);
    SudokuGridDLX::addBoxRuleValues(sudokuGrid);
};

void SudokuGridDLX::addCellRuleValues(int sudokuGrid[9*9*9][9*9*4])
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

void SudokuGridDLX::addRowRuleValues(int sudokuGrid[9*9*9][9*9*4])
{
    for(int row = 1; row <= boardSize; row++){
            for(int number = 1; number <= boardSize; number++, gridColumnPosition++){
                for(int column = 1; column <= boardSize; column++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

void SudokuGridDLX::addColumnRuleValues(int sudokuGrid[9*9*9][9*9*4])
{
    for(int column = 1; column <= boardSize; column++){
            for(int number = 1; number <= boardSize; number++, gridColumnPosition++){
                for(int row = 1; row <= boardSize; row++){
                    sudokuGrid[SudokuGridDLX::getGridRow(row, column, number)][gridColumnPosition] = 1;
                }
            }
    }
};

void SudokuGridDLX::addBoxRuleValues(int sudokuGrid[9*9*9][9*9*4])
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