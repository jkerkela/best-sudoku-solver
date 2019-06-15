#ifndef DANCINGLINKS_H
#define DANCINGLINKS_H
#include <string>
using namespace std;

class DancingLinkNode;
class ColumnNode;

class DancingLinkNode
{
        public:
            DancingLinkNode *L;
            DancingLinkNode *R;
            DancingLinkNode *U;
            DancingLinkNode *D;
            //ORIG: ColumnNode props / types
            ColumnNode *C;
            int size; // number of ones in current column
            string name;
            // re-type and assign to column node, if possible
            DancingLinkNode();
            DancingLinkNode(DancingLinkNode *c);
            DancingLinkNode hookRight(DancingLinkNode n1);
            DancingLinkNode hookDown(DancingLinkNode n1);
            void unlinkLR();
            void relinkLR();
            void unlinkUD();
            void relinkUD();
};

class ColumnNode : public DancingLinkNode
    {
        public:
            ColumnNode(string name);
            DancingLinkNode parent;
            void cover();
            void uncover();
    };

#endif // DANCINGLINKS_H