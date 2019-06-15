#ifndef SOLUTIONHANDLER_H
#define SOLUTIONHANDLER_H

#include <list>
#include <vector>
#include "dlxnodes/DancingLinks.h"

class SolutionHandler {
    public:
        void handleSolution(vector<DancingLinkNode> answer);
    private:
        vector<vector<int>> parseBoard(vector<DancingLinkNode> answer);
        void printSolution(vector<vector<int>> solution);
};

#endif // SOLUTIONHANDLER_H