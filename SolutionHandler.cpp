#include "SolutionHandler.h"
#include "DancingLinks.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
using std::cout;
using std::endl;
using std::string;
using std::vector;

const int boardSize = 9;

void SolutionHandler::handleSolution(vector<DancingLinkNode*> answer) {
    int** sudokuGrid = parseBoard(answer);
    printSolution(sudokuGrid);
}

int** SolutionHandler::parseBoard(vector<DancingLinkNode*> answer) {
    //vector<vector<int>> result;
    int** result = initializeSolutionArray();
    for(DancingLinkNode* n : answer){
        DancingLinkNode* node = n;
        int min = stoi(node->C->name);
        for(DancingLinkNode* tmp = n->R; tmp != n; tmp = tmp->R){
            int val = stoi(tmp->C->name);
            if (val < min){
                min = val;
                node = tmp;
            }
        }
        int ans1 = stoi(node->C->name);
        int ans2 = stoi(node->R->C->name);
        int r = ans1 / boardSize;
        int c = ans1 % boardSize;
        int num = (ans2 % boardSize) + 1;
        result[r][c] = num;
    }
    return result;
}

void SolutionHandler::printSolution(int** solutionGrid) {
    int n = boardSize;
    for(int i = 0; i < n; i++){
        string ret = "";
        for(int j = 0; j < n; j++){
            ret += std::to_string(solutionGrid[i][j]) + " ";
        }
        cout << ret << endl;
    }
}

int** SolutionHandler::initializeSolutionArray() {
    int** solutionGrid = new int*[9];
    for(int i = 0; i < 9; i++){
        solutionGrid[i] = new int[9];
    }
    return solutionGrid;
}
    