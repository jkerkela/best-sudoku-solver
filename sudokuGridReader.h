#ifndef SUDOKUGRIDREADER_H
#define SUDOKUGRIDREADER_H
using namespace std;

class SudokuGridReader 
{

private:
    const static string sudokuGridFilePath;
    string readSudokuCellsOrNull();
    int** sudokuGridFromString(string sudokuAsString); 
    int** initializeArray();
    
public:
    int** getSudokuGrid(); 
    
};

#endif // SUDOKUGRIDREADER_H