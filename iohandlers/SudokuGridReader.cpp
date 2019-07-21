#include "SudokuGridReader.h"
#include "../Constants.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int** SudokuGridReader::getSudokuGrid() {
    string sudokuAsString = readSudokuCellsOrNull();
    return sudokuGridFromString(sudokuAsString);
}

string SudokuGridReader::readSudokuCellsOrNull() {
    string sudokuGrid;
    ifstream sudokuGridFile;
    sudokuGridFile.open(sudokuGridFilePath);
    
    if (getline(sudokuGridFile, sudokuGrid)) {
        cout << "Initial Sudoku Grid: " + sudokuGrid << endl;
        return sudokuGrid;
    } else {
        cout << "Can't read file from path: " +  sudokuGridFilePath << endl;
    }
    return NULL;
}

int** SudokuGridReader::sudokuGridFromString(string sudokuAsString) {
    int** sudokuGrid = initializeArray();
    for (int i = 0; i < 81; i++) {
        char c = sudokuAsString[i];
        int row = i / 9;
        int col = i % 9;
        if(c != '.') {
            sudokuGrid[row][col] = c - '0';
        } else {
            sudokuGrid[row][col] = 0;
        }
    }
    return sudokuGrid;
}

int** SudokuGridReader::initializeArray() {
    int** sudokuGrid = 0;
    sudokuGrid = new int*[9];
    for (int i = 0; i < 9; i++) {
        sudokuGrid[i] = new int[9];
    }
    return sudokuGrid;
}
