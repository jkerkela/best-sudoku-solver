#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "sudokuGridReader.h"
using namespace std;

const string SudokuGridReader::sudokuGridFilePath = "./data/sudoku_grids.txt";

string SudokuGridReader::readSudokuCellsOrNull() 
{
    string sudokuGrid;
    ifstream sudokuGridFile;
    sudokuGridFile.open(sudokuGridFilePath);
    
    if (getline(sudokuGridFile, sudokuGrid))
    {
        cout << "Initial Sudoku Grid: " + sudokuGrid << endl;
        return sudokuGrid;
    }
    else {
        cout << "Can't read file from path: " + sudokuGridFilePath;
    }
    return NULL;
}
