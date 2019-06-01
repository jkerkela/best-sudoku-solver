using namespace std;

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "dlxnodes/ColumnNode.h"
#include "SudokuGridSolver.h"
#include "SudokuGridDLX.h"
#include "SudokuGridReader.h"

SudokuGridDLX sudokuGridDLX;
ColumnNode header;
int updates = 0;

void SudokuGridSolver::solve(int** sudokuGrid) 
{
   int** intialSudokuCoverGrid = sudokuGridDLX.initializeExactCoverGrid();
   int** sudokuCoverGridWithValues = sudokuGridDLX.addActualSudokuValuesToCoverGrid(sudokuGrid, intialSudokuCoverGrid);
   solveByDancingLinks(sudokuCoverGridWithValues);
}

void SudokuGridSolver::solveByDancingLinks(int** sudokuGrid) 
{
   header = makeDLXBoardWithLinks(sudokuGrid);
}

ColumnNode makeDLXBoardWithLinks(int** grid) 
{
    int columns = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.boardSize;
    int rows = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.sudokuRuleCount;
    ColumnNode headerNode = ColumnNode("header");
    vector<ColumnNode> columnNodes;

    for(int i = 0; i < columns; i++){
        ColumnNode n = ColumnNode(to_string(i));
        columnNodes.push_back(n);
        DancingLinkNode dLXNode = headerNode.hookRight(n);
        headerNode = *static_cast<ColumnNode*>(&dLXNode);
    }
    DancingLinkNode headerNodeR = *headerNode.R;
    headerNode = *headerNodeR.C;

    for(int i = 0; i < rows; i++){
        DancingLinkNode prev = NULL;
        for(int j = 0; j < columns; j++){
            if (grid[i][j] == 1){
                ColumnNode col = columnNodes.at(j);
                DancingLinkNode newNode = DancingLinkNode(col);
                if (!&prev)
                    prev = newNode;
                DancingLinkNode dlxNode = *col.U;
                dlxNode.hookDown(newNode);
                prev = prev.hookRight(newNode);
                col.size++;
            }
        }
    }
    headerNode.size = columns;
    return headerNode;
};

//TODO: continue here
void runSolver(){
    solutions = 0;
    updates = 0;
    answer = new LinkedList<DancingNode>();
    search(0);
    if(verbose) showInfo();
};
