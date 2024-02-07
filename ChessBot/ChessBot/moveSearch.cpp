#include"moveSearch.h"
#include"bitBoard.h"


    extern int tradeValue(moves moveList, char bB[8][8]) {
        std::pair<char, int> piece(bB[moveList.row][moveList.col], 0);

        std::pair<char, int> take(bB[moveList.tRow][moveList.tCol], 0);
        if (piece.first == 'p')
            piece.second = PAWN;
        if (piece.first == 'r')
            piece.second = ROOK;
        if (piece.first == 'n')
            piece.second = KNIGHT;
        if (piece.first == 'b')
            piece.second = BISHOP;
        if (piece.first == 'q')
            piece.second = QUEEN;
        if (piece.first == 'k')
            piece.second = KING;

        if (take.first == 'P')
            take.second = PAWN;
        if (take.first == 'R')
            take.second = ROOK;
        if (take.first == 'N')
            take.second = KNIGHT;
        if (take.first == 'B')
            take.second = BISHOP;
        if (take.first == 'Q')
            take.second = QUEEN;
        if (take.first == 'K')
            take.second = KING;
        return (take.second*50 - piece.second);
    }

    extern int position(moves moveList, char bB[8][8]) {
        int kingSafety = 0; // calculating king safety
        bool kingFound = 0; 
        if (moveList.castle == 1) {
            bB[0][0] = ' ';
            bB[0][2] = 'r';
            bB[0][3] = 'k';
            bB[0][4] = ' ';
            kingSafety += 90;
        }
        if (moveList.castle == 2) {
            bB[0][4] = ' ';
            bB[0][5] = 'r';
            bB[0][6] = 'k';
            bB[0][7] = ' ';
            kingSafety += 100;
        }
        char character = bB[moveList.row][moveList.col];
        bB[moveList.row][moveList.col] = ' ';
        if (moveList.promo != 0) {
            char b[4] = { 'q','n','b','r' };
            character = b[moveList.promo];
        }
        bB[moveList.tRow][moveList.tCol] = character;


        //DONT BLUNDER TO PAWN
        if (character != 'p') {
            if (bB[moveList.tRow + 1][moveList.tCol-1] == 'P') {
                return 0;
            }
            if (bB[moveList.tRow + 1][moveList.tCol + 1] == 'P') {
                return 0;
            }
            if (bB[moveList.row + 1][moveList.col - 1] == 'P') {
                return 0;
            }
            if (bB[moveList.col + 1][moveList.col + 1] == 'P') {
                return 0;
            }
        }

        std::vector<moves> moveL;
        std::vector<moves> incomingList;



        for (int row = 0; row < 8; row++) { // Finding all possible moves for black
            for (int col = 0; col < 8; col++) {
                if (islower(bB[row][col])) {
                    incomingList = generateMoveForPiece(row, col, bB, rookMove);
                    moveL.insert(moveL.end(), incomingList.begin(), incomingList.end());
                }
            }
        }
        int vision = moveL.size() * 4.1; // Spaces Occupied and have vision on

        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 8; col++) {
                if (bB[row][col] == 'k') {
                    if (row == 0)
                        kingSafety += 2;
                    for (int i = -1; i < 2 && col + i >= 0 && col + i < 8; i++) {
                        if (bB[row + 1][col + i] != ' ') {
                            kingSafety += 5;
                            if (bB[row + 1][col + i] == 'p') {
                                kingSafety += 5;
                            }
                        }
                    }
                }
            }
        }
        return kingSafety + vision;
    }
    extern moves moveSearch(std::vector<moves> moveList, char bB[8][8]) {
        int bestScore = 0;
        int positionV = 0;
        int move = 0;
        for (int i = 0; i < moveList.size(); i++) {
            int tradeV = 0;
            if (isupper(bB[moveList.at(i).tRow][moveList.at(i).tCol])) {
                tradeV = tradeValue(moveList.at(i), bB);
            }
            positionV = position(moveList.at(i), bB);

            if (tradeV + positionV >= bestScore) {
                bestScore = tradeV + positionV;
                move = i;
            }
        }
        return moveList.at(move);
    }