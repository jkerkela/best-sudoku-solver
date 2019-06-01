#ifndef DANCINGLINKNODE_H
#define DANCINGLINKNODE_H
using namespace std;

#include "ColumnNode.h"

class DancingLinkNode
{
    public:
        class ColumnNode;
        DancingLinkNode *L;
        DancingLinkNode *R;
        DancingLinkNode *U;
        DancingLinkNode *D;
        ColumNode *C;
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
