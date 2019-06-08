#include "SolutionHandler.h"
#include <iostream>
#include <stdio.h>
using namespace std;

const int boardSize = 9;

void SolutionHandler::handleSolution(list<DancingLinkNode> answer) {
    int** sudokuGrid = parseBoard(answer);
}

int** SolutionHandler::parseBoard(list<DancingLinkNode> answer) {
    int result[boardSize][boardSize];
    for(DancingLinkNode n : answer){
            DancingLinkNode rcNode = n;
            int min = stoi(rcNode.C.name);
            for(DancingLinkNode tmp = *n.R; &tmp != &n; tmp = *tmp.R){
                int val = stoi(tmp.C.name);
                if (val < min){
                    min = val;
                    rcNode = tmp;
                }
            }
            int ans1 = stoi(rcNode.C.name);
            DancingLinkNode nodeR = *rcNode.R;
            int ans2 = stoi(nodeR.C.name);
            int r = ans1 / boardSize;
            int c = ans1 % boardSize;
            int num = (ans2 % boardSize) + 1;
            result[r][c] = num;
        }
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
    