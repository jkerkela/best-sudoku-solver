#include "DancingLinks.h"
#include "../SudokuGridSolver.h"

#include <assert.h>
#include <stdio.h>

DancingLinkNode::DancingLinkNode() {
    this->L = this->R = this->U = this->D = this;
}

DancingLinkNode::DancingLinkNode(ColumnNode* c) {
    this->L = this->R = this->U = this->D = this;
    this->C = c;
}

// hooks node n1 `below` current node
DancingLinkNode* DancingLinkNode::hookDown(DancingLinkNode* n1) {
    assert (C == n1->C);
    n1->D = this->D;
    n1->D->U = n1;
    n1->U = this;
    this->D = n1;
    return n1;
}

// hooke a node n1 to the right of current node
DancingLinkNode* DancingLinkNode::hookRight(DancingLinkNode* n1) {
    n1->R = R;
    n1->R->L = n1;
    n1->L = this;
    this->R = n1;
    return n1;
}

void DancingLinkNode::unlinkLR() {
    this->L->R = R;
    this->R->L = L;
}

void DancingLinkNode::relinkLR() {
    this->L->R = this->R->L = this;
}

void DancingLinkNode::unlinkUD() {
    this->U->D = D;
    this->D->U = U;
}

void DancingLinkNode::relinkUD() {
    this->U->D = this->D->U = this;
}
