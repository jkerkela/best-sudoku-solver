#ifndef SOLUTIONHANDLER_H
#define SOLUTIONHANDLER_H

#include <list>
#include <vector>
#include "DancingLinks.h"

class SolutionHandler {
    public:
        void handleSolution(std::vector<DancingLinkNode*> answer);
    private:
        std::vector<std::vector<int>> parseBoard(std::vector<DancingLinkNode*> answer);
        void printSolution(std::vector<std::vector<int>> solution);
};

#endif // SOLUTIONHANDLER_H