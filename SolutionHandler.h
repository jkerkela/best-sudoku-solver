#ifndef SOLUTIONHANDLER_H
#define SOLUTIONHANDLER_H

#include <list>
#include <vector>
#include "DancingLinks.h"

class SolutionHandler {
    public:
        void handleSolution(std::vector<DancingLinkNode*> answer);
    private:
        int** parseBoard(std::vector<DancingLinkNode*> answer);
        void printSolution(int** solutionGrid);
        int** initializeSolutionArray();
};

#endif // SOLUTIONHANDLER_H