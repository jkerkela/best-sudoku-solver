#ifndef COLUNMNODE_H
#define COLUNMNODE_H
using namespace std;

#include <string>
#include "DancingLinkNode.h"

class ColumnNode : public DancingLinkNode
{
    public:
        int size; // number of ones in current column
        ColumnNode(string name);
        void cover();
        void uncover();

    private:
    string name;
    DancingLinkNode parent;
    
};

#endif // COLUNMNODE_H