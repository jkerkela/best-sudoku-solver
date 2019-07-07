#include <string>
#include "DancingLinks.h"
using std::string;

ColumnNode::ColumnNode(string name): DancingLinkNode() {
    //ORIG:
    //super();
    this->L = this->R = this->U = this->D = this;
    this->C = this;
    size = 0;
    name = name;
}

ColumnNode::ColumnNode(DancingLinkNode& dancingLinkNode): DancingLinkNode() {
    //ORIG:
    //super();
    this->L = dancingLinkNode.L;
    this->R = dancingLinkNode.R;
    this->U = dancingLinkNode.U;
    this->D = dancingLinkNode.D;
    this->C = dancingLinkNode.C;
    size = dancingLinkNode.size;
    name = dancingLinkNode.name;
}

void ColumnNode::cover(){
    unlinkLR();
    for(DancingLinkNode* i = this->D; i != this; i = i->D){
        for(DancingLinkNode* j = i->R; j != i; j = j->R){
            j->unlinkUD();
            ColumnNode* cNode = j->C;
            cNode->size--;
        }
    }
    //header.size--; // not part of original
}

void ColumnNode::uncover(){
    for(DancingLinkNode* i = this->U; i != this; i = i->U){
        for(DancingLinkNode* j = i->L; j != i; j = j->L){
            ColumnNode* cNode = j->C;
            cNode->size++;
            j->relinkUD();
        }
    }
    relinkLR();
    //header.size++; // not part of original
}