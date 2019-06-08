using namespace std;

#include <iostream>
#include <List>
#include <stdio.h>
#include <string>
#include <vector>
#include "dlxnodes/ColumnNode.h"
#include "SudokuGridSolver.h"
#include "SudokuGridDLX.h"
#include "SudokuGridReader.h"
#include "SolutionHandler.h"

SudokuGridDLX sudokuGridDLX;
ColumnNode header;
SolutionHandler handler;
int updates = 0;
int solutions = 0;
int updates = 0;
vector<DancingLinkNode> answer;

void SudokuGridSolver::solve(int** sudokuGrid) 
{
   int** intialSudokuCoverGrid = sudokuGridDLX.initializeExactCoverGrid();
   int** sudokuCoverGridWithValues = sudokuGridDLX.addActualSudokuValuesToCoverGrid(sudokuGrid, intialSudokuCoverGrid);
   solveByDancingLinks(sudokuCoverGridWithValues);
}

void SudokuGridSolver::solveByDancingLinks(int** sudokuGrid) 
{
    header = makeDLXBoardWithLinks(sudokuGrid);
    solutions = 0;
    updates = 0;
    search(0);
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
// Parses through 2d binary array elements (nodes) eliminating non-valid nodes
void search(int k){
    if (header.R == &header){ // all the columns removed
        cout << "Solution #" << solutions << endl;
        handler.handleSolution(answer);
        solutions++;
    } else {
        ColumnNode c = selectColumnNodeHeuristic();
        c.cover();

        for(DancingLinkNode r = *c.D; &r != &c; r = *r.D){
            answer.push_back(r);

            for(DancingLinkNode j = *r.R; &j != &r; j = *j.R){
                j.C.cover();
            }

            search(k + 1);

            int lastElement = answer.size() - 1;
            r = answer.at(lastElement);
            answer.erase(answer.begin() + lastElement);
            c = r.C;

            for(DancingLinkNode j = *r.L; &j != &r; j = *j.L){
                j.C.uncover();
            }
        }
        c.uncover();
    }
}

ColumnNode selectColumnNodeHeuristic(){
    int min = INT_MAX;
    ColumnNode ret = NULL;
    ColumnNode cNode = *static_cast<ColumnNode*>(header.R);
    for(cNode; &cNode != &header; cNode = *static_cast<ColumnNode*>(cNode.R)){
        if (cNode.size < min){
            min = cNode.size;
            ret = cNode;
        }
    }
    return ret;
}
