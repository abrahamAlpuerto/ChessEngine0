#pragma once
#include<vector>
#include<iostream>
namespace moveGeneration {
    struct moves {
        int row, col, tRow, tCol;
        int promo = 0; // 1 = q 2 = n 3 = r 4 = b
        int castle = 0; //0 no castle 1 castle long 2 castle short
    };
    extern std::vector<moves> generateMoveForPiece(int row, int col, char bB[8][8], bool castleMove[3]);
    extern std::vector<int> moveCords(moves);
}