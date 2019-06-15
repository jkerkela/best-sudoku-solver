#include "SolutionHandler.h"
#include "dlxnodes/DancingLinks.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
using namespace std;

const int boardSize = 9;

void SolutionHandler::handleSolution(list<DancingLinkNode> answer) {
    vector<vector<int>> sudokuGrid = parseBoard(answer);
    printSolution(sudokuGrid);
}

vector<vector<int>> SolutionHandler::parseBoard(list<DancingLinkNode> answer) {
    vector<vector<int>> result;
    for(DancingLinkNode n : answer){
        DancingLinkNode node = n;
        DancingLinkNode nodeC = *node.C;
        int min = stoi(nodeC.name);
        for(DancingLinkNode tmp = *n.R; &tmp != &n; tmp = *tmp.R){
            DancingLinkNode cNode = *tmp.C;
            int val = stoi(cNode.name);
            if (val < min){
                min = val;
                node = tmp;
            }
        }
        int ans1 = stoi(nodeC.name);
        DancingLinkNode nodeR = *node.R;
        DancingLinkNode nodeRC = *nodeR.C;
        int ans2 = stoi(nodeRC.name);
        int r = ans1 / boardSize;
        int c = ans1 % boardSize;
        int num = (ans2 % boardSize) + 1;
        result[r][c] = num;
    }
    return result;
}

void SolutionHandler::printSolution(vector<vector<int>> result){
    int n = boardSize;
    for(int i = 0; i < n; i++){
        string ret = "";
        for(int j = 0; j < n; j++){
            ret += result[i][j] + " ";
        }
        cout << ret << endl;
    }
}
    