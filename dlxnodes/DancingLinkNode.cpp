using namespace std;
#include <assert.h>
#include <stdio.h>
#include "DancingLinks.h"

DancingLinks::DancingLinkNode::DancingLinkNode() {
    L = R = U = D = this;
}

DancingLinks::DancingLinkNode::DancingLinkNode(ColumnNode *c) {
    //this(); not sure what to do on this, maybe:
    DancingLinkNode node = DancingLinkNode::DancingLinkNode();
    *node.D = c;
}

// hooks node n1 `below` current node
DancingLinkNode DancingLinks::DancingLinkNode::hookDown(DancingLinkNode n1){
    assert (&this->C == &n1.C);
    n1.D = this->D;
    DancingLinkNode n1D = *n1.D;
    *n1D.U = n1;
    //n1.D.U = n1;
    n1.U = this;
    this->D = &n1;
    return n1;
}

// hooke a node n1 to the right of current node
DancingLinkNode DancingLinks::DancingLinkNode::hookRight(DancingLinkNode n1){
    n1.R = this->R;
    DancingLinkNode n1R = *n1.R;
    *n1R.L = n1;
    //n1.R.L = n1;
    n1.L = this;
    this->R = &n1;
    return n1;
}

void DancingLinks::DancingLinkNode::unlinkLR(){
    DancingLinkNode iL = *this->L;
    iL.R = this->R;
    //this->L.R = this->R;
    DancingLinkNode iR = *this->R;
    iR.L = this->L;
    //this->R.L = this->L;
    //updates++;
}

void DancingLinks::DancingLinkNode::relinkLR(){
    DancingLinkNode iL = *this->L;
    DancingLinkNode iR = *this->R;
    iL.R = iR.L;
    //this->L.R = this->R.L = this;
    //updates++;
}

void DancingLinks::DancingLinkNode::unlinkUD(){
    DancingLinkNode iU = *this->U;
    iU.D = this->D;
    //this->U.D = this->D;
    DancingLinkNode iD = *this->D;
    iD.U = this->U;
    //this->D.U = this->U;
    //updates++;
}

void DancingLinks::DancingLinkNode::relinkUD(){
    DancingLinkNode iU = *this->U;
    iU.D = this;
    DancingLinkNode iD = *this->D;
    iD.U = this;
    //this->U.D = this->D.U = this;
    //updates++;
}
