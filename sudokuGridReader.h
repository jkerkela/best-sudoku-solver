#ifndef SUDOKUGRIDREADER_H
#define SUDOKUGRIDREADER_H

class SudokuGridReader 
{

private:
    const static std::string sudokuGridFilePath;
    std::string readSudokuCellsOrNull();
    int** sudokuGridFromString(std::string sudokuAsString); 
    int** initializeArray();
    
public:
    int** getSudokuGrid(); 
    
};

#endif // SUDOKUGRIDREADER_H