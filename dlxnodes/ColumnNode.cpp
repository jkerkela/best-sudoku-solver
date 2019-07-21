#include "DancingLinks.h"

#include <string>

using std::string;

ColumnNode::ColumnNode(string name): DancingLinkNode() {
    this->L = this->R = this->U = this->D = this->C = this;
    this->size = 0;
    this->name = name;
}

void ColumnNode::cover() {
    unlinkLR();
    for(DancingLinkNode* i = this->D; i != this; i = i->D){
        for(DancingLinkNode* j = i->R; j != i; j = j->R){
            j->unlinkUD();
            ColumnNode* cNode = j->C;
            cNode->size--;
        }
    }
}

void ColumnNode::uncover() {
    for(DancingLinkNode* i = this->U; i != this; i = i->U){
        for(DancingLinkNode* j = i->L; j != i; j = j->L){
            ColumnNode* cNode = j->C;
            cNode->size++;
            j->relinkUD();
        }
    }
    relinkLR();
}