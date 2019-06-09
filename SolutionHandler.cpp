#include "SolutionHandler.h"
#include <iostream>
#include <stdio.h>
using namespace std;

const int boardSize = 9;

void SolutionHandler::handleSolution(vector<DancingLinkNode> answer) {
    int** sudokuGrid = parseBoard(answer);
}

int** SolutionHandler::parseBoard(vector<DancingLinkNode> answer) {
    int result[boardSize][boardSize];
    for(DancingLinkNode n : answer){
            DancingLinkNode node = n;
            ColumnNode nodeC = *node.C;
            int min = stoi(nodeC.name);
            for(DancingLinkNode tmp = *n.R; &tmp != &n; tmp = *tmp.R){
                ColumnNode cNode = *tmp.C;
                int val = stoi(cNode.name);
                if (val < min){
                    min = val;
                    node = tmp;
                }
            }
            int ans1 = stoi(nodeC.name);
            DancingLinkNode nodeR = *node.R;
            ColumnNode nodeRC = *nodeR.C;
            int ans2 = stoi(nodeRC.name);
            int r = ans1 / boardSize;
            int c = ans1 % boardSize;
            int num = (ans2 % boardSize) + 1;
            result[r][c] = num;
        }
    return result;
}

void printSolution(int** result){
        int n = boardSize;
        for(int i = 0; i < n; i++){
            string ret = "";
            for(int j = 0; j < n; j++){
                ret += result[i][j] + " ";
            }
            cout << ret << endl;
        }
    }
    