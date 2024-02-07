#include"bitBoard.h"
#include"moveGeneration.h"
#include<iostream>
#include<string>
#include<time.h>

int main()
{
    srand(time(0));
    bitBoard chessGame;
    while (true) {

        chessGame.printBoard();
        std::cout << "Input a Move: ";
        std::string wMove;
        std::cin >> wMove;
        chessGame.whiteMove(wMove);
        chessGame.botMove();
    }
}