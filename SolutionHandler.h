#ifndef SOLUTIONHANDLER_H
#define SOLUTIONHANDLER_H

#include <vector>
#include "dlxnodes/DancingLinks.h"

class SolutionHandler {
    public:
        void handleSolution(vector<DancingLinkNode> answer);
    private:
        int** parseBoard(vector<DancingLinkNode> answer);
        void printSolution(int** solution);
};

#endif // SOLUTIONHANDLER_H