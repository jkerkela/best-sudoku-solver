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

SudokuGridDLX sudokuGridDLX;
ColumnNode header;
int updates = 0;
int solutions = 0;
int updates = 0;
list<DancingLinkNode> answer;

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
// Heart of the algorithm
private void search(int k){
    if (header.R == header){ // all the columns removed
        if(verbose){
            System.out.println("-----------------------------------------");
            System.out.println("Solution #" + solutions + "\n");
        }
        handler.handleSolution(answer);
        if(verbose){
            System.out.println("-----------------------------------------");
        }
        solutions++;
    } else{
        ColumnNode c = selectColumnNodeHeuristic();
        c.cover();

        for(DancingNode r = c.D; r != c; r = r.D){
            answer.add(r);

            for(DancingNode j = r.R; j != r; j = j.R){
                j.C.cover();
            }

            search(k + 1);

            r = answer.remove(answer.size() - 1);
            c = r.C;

            for(DancingNode j = r.L; j != r; j = j.L){
                j.C.uncover();
            }
        }
        c.uncover();
    }
}

private ColumnNode selectColumnNodeNaive(){
    return (ColumnNode) header.R;
}

private ColumnNode selectColumnNodeHeuristic(){
    int min = Integer.MAX_VALUE;
    ColumnNode ret = null;
    for(ColumnNode c = (ColumnNode) header.R; c != header; c = (ColumnNode) c.R){
        if (c.size < min){
            min = c.size;
            ret = c;
        }
    }
    return ret;
}
