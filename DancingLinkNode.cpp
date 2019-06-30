#include <assert.h>
#include <stdio.h>
#include "DancingLinks.h"

DancingLinkNode::DancingLinkNode() {
    L = R = U = D = this;
}

DancingLinkNode::DancingLinkNode(ColumnNode c) {
    //ORIG:
    //this(); 
    L = R = U = D = this;
    C = &c;
}

// hooks node n1 `below` current node
DancingLinkNode DancingLinkNode::hookDown(DancingLinkNode n1){
    //TODO: gives assert err
    //assert (&C == &n1.C);
    n1.D = this->D;
    DancingLinkNode n1D = *n1.D;
    n1D.U = &n1;
    //ORIG:
    //n1.D.U = n1;
    n1.U = this;
    this->D = &n1;
    return n1;
}

// hooke a node n1 to the right of current node
DancingLinkNode DancingLinkNode::hookRight(DancingLinkNode n1){
    n1.R = this->R;
    DancingLinkNode n1R = *n1.R;
    n1R.L = &n1;
    //ORIG:
    //n1.R.L = n1;
    n1.L = this;
    this->R = &n1;
    return n1;
}

void DancingLinkNode::unlinkLR(){
    DancingLinkNode iL = *L;
    iL.R = this->R;
    //ORIG:
    //L.R = R;
    DancingLinkNode iR = *R;
    iR.L = this->L;
    //ORIG:
    //R.L = L;
    //updates++;
}

void DancingLinkNode::relinkLR(){
    DancingLinkNode iL = *L;
    DancingLinkNode iR = *R;
    iL.R = iR.L = this;
    //ORIG:
    //L.R = R.L = this;
    //updates++;
}

void DancingLinkNode::unlinkUD(){
    DancingLinkNode iU = *U;
    iU.D = D;
    //ORIG:
    //U.D = D;
    DancingLinkNode iD = *D;
    iD.U = U;
    //ORIG:
    //D.U = U;
    //updates++;
}

void DancingLinkNode::relinkUD(){
    DancingLinkNode iU = *U;
    DancingLinkNode iD = *D;
    iU.D = iD.U = this;
    //ORIG:
    //U.D = D.U = this;
    //updates++;
}
