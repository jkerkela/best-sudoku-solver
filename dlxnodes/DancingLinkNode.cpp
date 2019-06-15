using namespace std;
#include <assert.h>
#include <stdio.h>
#include "DancingLinks.h"

DancingLinkNode::DancingLinkNode() {
    L = R = U = D = this;
}

DancingLinkNode::DancingLinkNode(ColumnNode *c) {
    //ORIG:
    //this(); 
    DancingLinkNode node = DancingLinkNode::DancingLinkNode();
    node.C = static_cast<ColumnNode*>(c);
}

// hooks node n1 `below` current node
DancingLinkNode DancingLinkNode::hookDown(DancingLinkNode n1){
    assert (&this->C == &n1.C);
    n1.D = this->D;
    DancingLinkNode n1D = *n1.D;
    *n1D.U = n1;
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
    *n1R.L = n1;
    //ORIG:
    //n1.R.L = n1;
    n1.L = this;
    this->R = &n1;
    return n1;
}

void DancingLinkNode::unlinkLR(){
    DancingLinkNode iL = *this->L;
    iL.R = this->R;
    //ORIG:
    //this->L.R = this->R;
    DancingLinkNode iR = *this->R;
    iR.L = this->L;
    //ORIG:
    //this->R.L = this->L;
    //updates++;
}

void DancingLinkNode::relinkLR(){
    DancingLinkNode iL = *this->L;
    DancingLinkNode iR = *this->R;
    iL.R = iR.L;
    //ORIG:
    //this->L.R = this->R.L = this;
    //updates++;
}

void DancingLinkNode::unlinkUD(){
    DancingLinkNode iU = *this->U;
    iU.D = this->D;
    //ORIG:
    //this->U.D = this->D;
    DancingLinkNode iD = *this->D;
    iD.U = this->U;
    //ORIG:
    //this->D.U = this->U;
    //updates++;
}

void DancingLinkNode::relinkUD(){
    DancingLinkNode iU = *this->U;
    iU.D = this;
    DancingLinkNode iD = *this->D;
    iD.U = this;
    //ORIG:
    //this->U.D = this->D.U = this;
    //updates++;
}
