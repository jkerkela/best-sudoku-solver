#ifndef DANCINGLINKNODE_H
#define DANCINGLINKNODE_H
using namespace std;

#include "ColumnNode.h"

class DancingLinkNode
{
    public:
        DancingLinkNode *L;
        DancingLinkNode *R;
        DancingLinkNode *U;
        DancingLinkNode *D;
        ColumnNode C;
        DancingLinkNode();
        DancingLinkNode(ColumnNode *c);
        DancingLinkNode hookRight(DancingLinkNode n1);
        DancingLinkNode hookDown(DancingLinkNode n1);
        void unlinkLR();
        void relinkLR();
        void unlinkUD();
        void relinkUD();

    private:
};

#endif // DANCINGLINKNODE_H
