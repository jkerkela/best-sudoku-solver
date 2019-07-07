#ifndef DANCINGLINKS_H
#define DANCINGLINKS_H
#include <string>

class DancingLinkNode;
class ColumnNode;

class DancingLinkNode
{
        public:
            DancingLinkNode *L;
            DancingLinkNode *R;
            DancingLinkNode *U;
            DancingLinkNode *D;
            ColumnNode *C;
            int size; // number of ones in current column
            std::string name;
            DancingLinkNode();
            DancingLinkNode(ColumnNode* c);
            DancingLinkNode* hookRight(DancingLinkNode* n1);
            DancingLinkNode* hookDown(DancingLinkNode* n1);
            void unlinkLR();
            void relinkLR();
            void unlinkUD();
            void relinkUD();
};

class ColumnNode : public DancingLinkNode
    {
        public:
            ColumnNode(std::string name);
            void cover();
            void uncover();
    };

#endif // DANCINGLINKS_H