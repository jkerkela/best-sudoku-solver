#include "SolutionHandler.h"
#include "dlxnodes/DancingLinks.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
using namespace std;

const int boardSize = 9;

void SolutionHandler::handleSolution(list<DancingLinks::DancingLinkNode> answer) {
    int** sudokuGrid = parseBoard(answer);
    printSolution(sudokuGrid);
}

vector<vector<int>> SolutionHandler::parseBoard(list<DancingLinks::DancingLinkNode> answer) {
    vector<vector<int>> result;
    for(DancingLinks::DancingLinkNode n : answer){
        DancingLinks::DancingLinkNode node = n;
        DancingLinks::DancingLinkNode nodeC = *node.C;
        int min = stoi(nodeC.name);
        for(DancingLinks::DancingLinkNode tmp = *n.R; &tmp != &n; tmp = *tmp.R){
            DancingLinks::DancingLinkNode cNode = *tmp.C;
            int val = stoi(cNode.name);
            if (val < min){
                min = val;
                node = tmp;
            }
        }
        int ans1 = stoi(nodeC.name);
        DancingLinks::DancingLinkNode nodeR = *node.R;
        DancingLinks::DancingLinkNode nodeRC = *nodeR.C;
        int ans2 = stoi(nodeRC.name);
        int r = ans1 / boardSize;
        int c = ans1 % boardSize;
        int num = (ans2 % boardSize) + 1;
        result[r][c] = num;
    }
    return result;
}

void SolutionHandler::printSolution(int** result){
    int n = boardSize;
    for(int i = 0; i < n; i++){
        string ret = "";
        for(int j = 0; j < n; j++){
            ret += result[i][j] + " ";
        }
        cout << ret << endl;
    }
}
    