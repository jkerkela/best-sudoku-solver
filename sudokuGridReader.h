#ifndef SUDOKUGRIDREADER_H
#define SUDOKUGRIDREADER_H
using namespace std;

class SudokuGridReader 
{

private:
    const static string sudokuGridFilePath;
    
public:
    string readSudokuCellsOrNull(); 
    
};

#endif // SUDOKUGRIDREADER_H