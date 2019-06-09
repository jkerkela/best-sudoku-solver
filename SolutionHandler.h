#ifndef SOLUTIONHANDLER_H
#define SOLUTIONHANDLER_H

#include <list>
#include "dlxnodes/DancingLinks.h"

class SolutionHandler {
    public:
        void handleSolution(list<DancingLinks::DancingLinkNode> answer);
    private:
        int** parseBoard(list<DancingLinks::DancingLinkNode> answer);
        void printSolution(int** solution);
};

#endif // SOLUTIONHANDLER_H