#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#include <string>
#include "DancingLinks.h"
#include "SudokuGridSolver.h"
#include "SudokuGridDLX.h"
#include "SudokuGridReader.h"
#include "SolutionHandler.h"
using std::cout;
using std::endl;
using std::vector;
using std::to_string;

SudokuGridDLX sudokuGridDLX;
DancingLinkNode* header;
SolutionHandler* handler;
int updates = 0;
int solutions = 0;
vector<DancingLinkNode*> answer;

void SudokuGridSolver::solve(int** sudokuGrid) 
{
   int** exactCoverGrid = initializeArray();
   sudokuGridDLX.initializeExactCoverGrid(exactCoverGrid);
   sudokuGridDLX.addActualSudokuValuesToCoverGrid(sudokuGrid, exactCoverGrid);
   solveByDancingLinks(exactCoverGrid);
}

int** SudokuGridSolver::initializeArray() 
{
    int** exactCoverGrid = new int*[9 * 9 * 9];
    for(int i = 0; i < (9 * 9 * 9); i++){
        exactCoverGrid[i] = new int[9 * 9 * 4];
    }
    return exactCoverGrid;
}

void SudokuGridSolver::solveByDancingLinks(int** sudokuGrid) 
{
    header = makeDLXBoardWithLinks(sudokuGrid);
    solutions = 0;
    updates = 0;
    search(0);
}

ColumnNode* SudokuGridSolver::makeDLXBoardWithLinks(int** grid) 
{
    int columns = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.sudokuRuleCount;
    int rows = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.boardSize;
    ColumnNode* headerNode = new ColumnNode("header");
    vector<ColumnNode*> columnNodes;

    for(int i = 0; i < columns; i++){
        ColumnNode* cNode = new ColumnNode(to_string(i));
        columnNodes.push_back(cNode);
        DancingLinkNode* dLXNode = headerNode->hookRight(cNode);
        headerNode = static_cast<ColumnNode*>(dLXNode);
    }
    DancingLinkNode* headerNodeR = headerNode->R;
    headerNode = static_cast<ColumnNode*>(headerNodeR->C);

    //TODO: this doesn't actually update columnNode refs (columnode->D will point to columnode itself)
    for(int i = 0; i < rows; i++){
        DancingLinkNode* pPrev = NULL;
        for(int j = 0; j < columns; j++){
            if (grid[i][j] == 1){
                ColumnNode* col = columnNodes.at(j);
                DancingLinkNode* newNode = new DancingLinkNode(col);
                if (pPrev == NULL)
                    pPrev = newNode;
                DancingLinkNode* dlxNode = col->U;
                dlxNode->hookDown(newNode);
                pPrev = pPrev->hookRight(newNode);
                col->size++;
            }
        }
    }
    headerNode->size = columns;
    return headerNode;
};

// Parses through 2d binary array elements (nodes) eliminating non-valid nodes
void SudokuGridSolver::search(int k){
    if (header->R == header){ // all the columns removed
        cout << "Solution #" << solutions << endl;
        handler->handleSolution(answer);
        solutions++;
    } else {
        ColumnNode* c = selectColumnNodeHeuristic();
        c->cover();

        //TODO: not going into this loop r == c always, see TODO in line 67
        for(DancingLinkNode* r = c->D; r != c; r = r->D){
            answer.push_back(r);
            for(DancingLinkNode* j = r->R; j != r; j = j->R){
                ColumnNode* cNode = j->C;
                cNode->cover();
            }

            search(k + 1);

            int lastElement = answer.size() - 1;
            r = answer.at(lastElement);
            answer.erase(answer.begin() + lastElement);
            c = r->C;

            for(DancingLinkNode* j = r->L; j != r; j = j->L){
                ColumnNode* cNode = j->C;
                cNode->uncover();
            }
        }
        c->uncover();
    }
}

ColumnNode* SudokuGridSolver::selectColumnNodeHeuristic(){
    int min = INT_MAX;
    ColumnNode* pRet = NULL;
    for(ColumnNode* cNode = static_cast<ColumnNode*>(header->R); cNode != header; cNode = static_cast<ColumnNode*>(cNode->R)){
        if (cNode->size < min){
            min = cNode->size;
            pRet = cNode;
        }
    }
    return pRet;
}
