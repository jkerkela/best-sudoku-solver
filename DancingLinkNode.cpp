#include <assert.h>
#include <stdio.h>
#include "DancingLinks.h"

DancingLinkNode::DancingLinkNode() {
    this->L = this->R = this->U = this->D = this;
}

DancingLinkNode::DancingLinkNode(ColumnNode* c) {
    this->L = this->R = this->U = this->D = this;
    this->C = c;
}

// hooks node n1 `below` current node
DancingLinkNode* DancingLinkNode::hookDown(DancingLinkNode* n1){
    assert (C == n1->C);
    n1->D = this->D;
    DancingLinkNode* n1D = n1->D;
    n1D->U = n1;
    n1->U = this;
    this->D = n1;
    return n1;
}

// hooke a node n1 to the right of current node
DancingLinkNode* DancingLinkNode::hookRight(DancingLinkNode* n1){
    n1->R = R;
    DancingLinkNode* n1R = n1->R;
    n1R->L = n1;
    n1->L = this;
    this->R = n1;
    return n1;
}

void DancingLinkNode::unlinkLR(){
    DancingLinkNode* iL = L;
    iL->R = R;
    DancingLinkNode* iR = R;
    iR->L = L;
    //updates++;
}

void DancingLinkNode::relinkLR(){
    DancingLinkNode* iL = L;
    DancingLinkNode* iR = R;
    iL->R = iR->L = this;
    //updates++;
}

void DancingLinkNode::unlinkUD(){
    DancingLinkNode* iU = U;
    iU->D = D;
    DancingLinkNode* iD = D;
    iD->U = U;
    //updates++;
}

void DancingLinkNode::relinkUD(){
    DancingLinkNode* iU = U;
    DancingLinkNode* iD = D;
    iU->D = iD->U = this;
    //updates++;
}
