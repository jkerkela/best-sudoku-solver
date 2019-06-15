using namespace std;
#include <string>
#include "DancingLinks.h"

ColumnNode::ColumnNode(string name){
    //ORIG:
    //super();
    parent = DancingLinkNode();
    size = 0;
    name = name;
    C = this;
}

void ColumnNode::cover(){
    unlinkLR();
    for(DancingLinkNode i = *this->D; &i != &parent; i = *i.D){
        for(DancingLinkNode j = *i.R; &j != &i; j = *j.R){
            j.unlinkUD();
            DancingLinkNode cNode = *j.C;
            cNode.size--;
        }
    }
    //header.size--; // not part of original
}

void ColumnNode::uncover(){
    for(DancingLinkNode i = *this->U; &i != &parent; i = *i.U){
        for(DancingLinkNode j = *i.L; &j != &i; j = *j.L){
            DancingLinkNode cNode = *j.C;
            cNode.size++;
            j.relinkUD();
        }
    }
    relinkLR();
    //header.size++; // not part of original
}