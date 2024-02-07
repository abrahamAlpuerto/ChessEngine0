#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<random>

extern bool rookMove[3]; //left black rook slot 0

class bitBoard {
public:

    bitBoard(std::string FEN) {}
    bitBoard();
    int moveType(std::string move);
    int findFile(char file);
    std::pair<int, int> findPiece(char piece,bool color); 
    int findRow(char piece, int file, int moveTo);
    void whiteMove(std::string move);
    void botMove();
    bool whiteBlackTurn();
    void printBoard();

    int moveNumber = 0;
    std::vector<int> one = { 1,6,2,6,0,0 };
    std::vector<int> two = { 0,5,1,6,0,0 };
    std::vector<int> three = { 1,3,2,3,0,0 };
    std::vector<int> four = { 1,2,2,2,0,0 };
    std::vector<int> five = { 0,6,2,5,0,0 };
    std::vector<int> six = { 0,0,0,0,0,2 };
    std::vector<std::vector<int>> opening;
    
    // king edge pawns
private:
     char board[8][8] = {       'r','n','b','q','k','b','n','r',
                                'p','p','p','p','p','p','p','p',
                                ' ',' ',' ',' ',' ',' ',' ',' ',
                                ' ',' ',' ',' ',' ',' ',' ',' ',
                                ' ',' ',' ',' ',' ',' ',' ',' ',
                                ' ',' ',' ',' ',' ',' ',' ',' ',
                                'P','P','P','P','P','P','P','P',
                                'R','N','B','Q','K','B','N','R'
    };

    int turn = 0; // 0 white 1 black
};