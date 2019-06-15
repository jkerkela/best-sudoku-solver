using namespace std;

#include <iostream>
#include <List>
#include <stdio.h>
#include <string>
#include "dlxnodes/DancingLinks.h"
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
list<DancingLinkNode> answer;

void SudokuGridSolver::solve(int** sudokuGrid) 
{
   sudokuGridDLX.initializeExactCoverGrid(sudokuGrid);
   sudokuGridDLX.addActualSudokuValuesToCoverGrid(sudokuGrid);
   solveByDancingLinks(sudokuGrid);
}

void SudokuGridSolver::solveByDancingLinks(int** sudokuGrid) 
{
    header = makeDLXBoardWithLinks(sudokuGrid);
    solutions = 0;
    updates = 0;
    search(0);
}

ColumnNode SudokuGridSolver::makeDLXBoardWithLinks(int** grid) 
{
    int columns = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.boardSize;
    int rows = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.sudokuRuleCount;
    DancingLinks::ColumnNode headerNode =  DancingLinks::ColumnNode("header");
    vector< DancingLinks::ColumnNode> columnNodes;

    for(int i = 0; i < columns; i++){
        DancingLinks::ColumnNode cNode =  DancingLinks::ColumnNode(to_string(i));
        columnNodes.push_back(cNode);
        DancingLinks::DancingLinkNode dLXNode = headerNode.hookRight(cNode);
        headerNode = *static_cast<DancingLinks::ColumnNode*>(&dLXNode);
    }
    DancingLinks::DancingLinkNode headerNodeR = *headerNode.R;
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
void SudokuGridSolver::search(int k){
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
                ColumnNode cNode = *j.C;
                cNode.cover();
            }

            search(k + 1);

            int lastElement = answer.size() - 1;
            r = answer.at(lastElement);
            answer.erase(answer.begin() + lastElement);
            c = *r.C;

            for(DancingLinkNode j = *r.L; &j != &r; j = *j.L){
                ColumnNode cNode = *j.C;
                cNode.uncover();
            }
        }
        c.uncover();
    }
}

ColumnNode SudokuGridSolver::selectColumnNodeHeuristic(){
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
