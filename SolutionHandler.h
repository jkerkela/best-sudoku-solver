#ifndef SOLUTIONHANDLER_H
#define SOLUTIONHANDLER_H

#include <list>
#include "dlxnodes/DancingLinkNode.h"

class SolutionHandler {
    public:
        void handleSolution(list<DancingLinkNode> answer);
    private:
        int** parseBoard(list<DancingLinkNode> answer);
        void printSolution(int** solution);
};

#endif // SOLUTIONHANDLER_H