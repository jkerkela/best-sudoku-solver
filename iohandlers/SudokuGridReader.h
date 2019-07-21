#ifndef SUDOKUGRIDREADER_H
#define SUDOKUGRIDREADER_H
#include <string>

class SudokuGridReader 
{

private:
    std::string readSudokuCellsOrNull();
    int** sudokuGridFromString(std::string sudokuAsString); 
    int** initializeArray();
    
public:
    int** getSudokuGrid(); 
    
};

#endif // SUDOKUGRIDREADER_H