#include <string>
#include "DancingLinks.h"
using std::string;

ColumnNode::ColumnNode(string name): DancingLinkNode() {
    //ORIG:
    //super();
    size = 0;
    name = name;
    L = R = U = D = this;
    C = this;
}

void ColumnNode::cover(){
    unlinkLR();
    for(DancingLinkNode i = *this->D; &i != this; i = *i.D){
        for(DancingLinkNode j = *i.R; &j != &i; j = *j.R){
            j.unlinkUD();
            ColumnNode cNode = *j.C;
            cNode.size--;
        }
    }
    //header.size--; // not part of original
}

void ColumnNode::uncover(){
    for(DancingLinkNode i = *this->U; &i != this; i = *i.U){
        for(DancingLinkNode j = *i.L; &j != &i; j = *j.L){
            ColumnNode cNode = *j.C;
            cNode.size++;
            j.relinkUD();
        }
    }
    relinkLR();
    //header.size++; // not part of original
}