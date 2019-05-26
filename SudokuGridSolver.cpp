#include <assert.h>
#include <iostream>
#include <stdio.h>
#include "SudokuGridSolver.h"
#include "SudokuGridDLX.h"
#include "SudokuGridReader.h"
using namespace std;

SudokuGridDLX sudokuGridDLX;
ColumnNode header;
int updates = 0;

//TODO: we may want to extract every dancing links related classes to own class, and just reference them from this class
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

//TODO: fix calls
ColumnNode makeDLXBoardWithLinks(int** grid) 
{
    int columns = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.boardSize;
    int rows = sudokuGridDLX.boardSize * sudokuGridDLX.boardSize * sudokuGridDLX.sudokuRuleCount;
    ColumnNode headerNode = ColumnNode("header");
    ArrayList<ColumnNode> columnNodes = new ArrayList<ColumnNode>();

    for(int i = 0; i < columns; i++){
        ColumnNode n = new SudokuGridSolver::ColumnNode(Integer.toString(i));
        columnNodes.add(n);
        headerNode = (ColumnNode) headerNode.hookRight(n);
    }
    headerNode = headerNode.R.C;

    for(int i = 0; i < rows; i++){
        DancingNode prev = null;
        for(int j = 0; j < columns; j++){
            if (grid[i][j] == 1){
                ColumnNode col = columnNodes.get(j);
                DancingNode newNode = new DancingNode(col);
                if (prev == null)
                    prev = newNode;
                col.U.hookDown(newNode);
                prev = prev.hookRight(newNode);
                col.size++;
            }
        }
    }

    headerNode.size = columns;
    
    return headerNode;
};

//TODO fix pointers
class DancingNode {

    DancingNode *L;
    DancingNode *R;
    DancingNode *U;
    DancingNode *D;
    ColumnNode *C;

    DancingNode(){
        L = R = U = D = this;
    }

    DancingNode(ColumnNode *c){
        //this(); not sure what to do on this, maybe:
        DancingNode();
        C = c;
    }

    // hooks node n1 `below` current node
    DancingNode hookDown(DancingNode n1){
        assert (this->C == n1.C);
        n1.D = this->D;
        n1.D.U = n1;
        n1.U = this;
        this->D = &n1;
        return n1;
    }

    // hooke a node n1 to the right of `this` node
    DancingNode hookRight(DancingNode n1){
        n1.R = this->R;
        n1.R.L = n1;
        n1.L = this;
        this->R = &n1;
        return n1;
    }

    void unlinkLR(){
        this->L.R = this->R;
        this->R.L = this->L;
        updates++;
    }

    void relinkLR(){
        this->L.R = this->R.L = this;
        updates++;
    }

    void unlinkUD(){
        this->U.D = this->D;
        this->D.U = this->U;
        updates++;
    }

    void relinkUD(){
        this->U.D = this->D.U = this;
        updates++;
    }
};

//TODO clean
class ColumnNode extends DancingNode {
    int size; // number of ones in current column
    String name;

    public ColumnNode(String n){
        super();
        size = 0;
        name = n;
        C = this;
    }

    void cover(){
        unlinkLR();
        for(DancingNode i = this->D; i != this; i = i.D){
            for(DancingNode j = i.R; j != i; j = j.R){
                j.unlinkUD();
                j.C.size--;
            }
        }
        header.size--; // not part of original
    }

    void uncover(){
        for(DancingNode i = this->U; i != this; i = i.U){
            for(DancingNode j = i.L; j != i; j = j.L){
                j.C.size++;
                j.relinkUD();
            }
        }
        relinkLR();
        header.size++; // not part of original
    }
}