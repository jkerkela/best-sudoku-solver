#ifndef DANCINGLINKS_H
#define DANCINGLINKS_H
#include <string>
using namespace std;

class ColumnNode;
class DancingLinkNode;

class DancingLinks
{
    class DancingLinkNode
    {
        public:
            DancingLinkNode *L;
            DancingLinkNode *R;
            DancingLinkNode *U;
            DancingLinkNode *D;
            ColumnNode *C;
            DancingLinkNode();
            DancingLinkNode(ColumnNode *c);
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
            int size; // number of ones in current column
            string name;
            DancingLinkNode parent;
            ColumnNode(string name);
            void cover();
            void uncover();
        
    };
};

#endif // DANCINGLINKS_H