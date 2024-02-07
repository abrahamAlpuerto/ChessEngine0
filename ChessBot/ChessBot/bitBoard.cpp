#include"bitBoard.h"
#include"moveGeneration.h"
#include"moveSearch.h"
using namespace moveGeneration;


bool rookMove[3] = { false, false, false };
bitBoard::bitBoard() {
    opening.push_back(one);
    opening.push_back(two);
    opening.push_back(three);
    opening.push_back(four);
    opening.push_back(five);
    opening.push_back(six);
}
int bitBoard::findFile(char file) {
    switch (file) {
    case 'a': case 'A': return 0;
    case 'b': case 'B': return 1;
    case 'c': case 'C': return 2;
    case 'd': case 'D': return 3;
    case 'e': case 'E': return 4;
    case 'f': case 'F': return 5;
    case 'g': case 'G': return 6;
    case 'h': case 'H': return 7;
    default: return -1; // Invalid input
    }
}
int bitBoard::moveType(std::string move) {
    int lengthMove = move.length();

    if (move[lengthMove - 1] == '+') { // Help Idenitfy... by getting rid of in check notation
        lengthMove--;
    }

    if (islower(move[0])) { // PAWN MOVES
        if (lengthMove == 2) {
            return 1;
        }
        else if (lengthMove == 4 && move[1] == 'x') {
            return 2;
        }
        else {
            return 3;
        }
    }

    if (move[0] == 'K' || move[0] == 'O') {
        if (move[0] == 'O') {
            if (lengthMove == 3) {
                return 5;
            }
            return 6;
        }
        return 4;
    }

    if (move[0] == 'Q') {
        return 7;
    }

    if (move[0] == 'B') {
        return 8;
    }

    if (move[0] == 'N') {
        return 9;
    }

    if (move[0] == 'R') {
        return 10;
    }
}
int bitBoard::findRow(char piece, int file, int moveTo) { // for Pawns
    int row = -1;
    if (piece == 'P') {
        for (int i = 8 - moveTo; i < 8; i++) {
            if (board[i][file] == piece) {
                row = i;
                break;
            }
        }
    }
    if (piece == 'N') {
        for (int i = 0; i < 8; i++) {
            if (board[i][file] == piece) {
                row = i;
                break;
            }
        }
    }
    return row;

}

std::pair<int,int> bitBoard::findPiece(char piece, bool color) { // color dark square = 1 light square = 0
    if (piece == 'B' && color) {
        for (int i = 0; i < 8; i++) {
            for (int j = (i+1)%2; j < 8; j+=2) {
                if (board[i][j] == piece) {
                    return std::make_pair(i, j);
                }
            }
        }
    }
    if (piece == 'B' && !color) {
        for (int i = 0; i < 8; i++) {
            for (int j = i % 2; j < 8; j += 2) {
                if (board[i][j] == piece) {
                    return std::make_pair(i, j);
                }
            }
        }
    }
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == piece) {
                return std::make_pair(i,j);
            }
        }
    }
}

void bitBoard::whiteMove(std::string move) {
    int moveNum = moveType(move);
    int lengthMove = move.length();
    if (move[move.length() - 1] == '+' || move[move.length() - 1] == '#') { // Help Idenitfy... by getting rid of in check notation
        lengthMove--;
    }
    
    if (moveNum == 1) { // p move
        int file = findFile(move[0]);
        int row = findRow('P', file, move[1]);
        board[row][file] = ' ';
        board[8 - (static_cast<int>(move[1]) - 48)][file] = 'P';
    }
    else if (moveNum == 2) { // p take
        int file = findFile(move[0]);
        int row = findRow('P', file, move[3]);
        board[row][file] = ' ';
        board[8 - (static_cast<int>(move[3]) - 48)][findFile(move[2])] = 'P';
    }
    else if (moveNum == 3) { // p promo
        int file = findFile(move[0]);
        int row = findRow('P', file, move[1]);

        board[row][file] = ' ';
        board[8 - (static_cast<int>(move[1]) - 48)][file] = move[3];

    }
    else if (moveNum == 4) { // k move
        std::pair<int, int> wherePiece = findPiece('K',0);

        board[wherePiece.first][wherePiece.second] = ' ';
        if (lengthMove == 3) {
            int file = findFile(move[1]);
            board[8 - (static_cast<int>(move[2]) - 48)][file] = 'K';
        }
        if (lengthMove == 4) {
            int file = findFile(move[2]);
            board[8 - (static_cast<int>(move[3]) - 48)][file] = 'K';
        }
    }
    else if (moveNum == 5) { // k castle short
        board[7][4] = ' ';
        board[7][5] = 'R';
        board[7][6] = 'K';
        board[7][7] = ' ';
    }
    else if (moveNum == 6) { // k castle long
        board[7][4] = ' ';
        board[7][2] = 'K';
        board[7][3] = 'R';
        board[7][0] = ' ';
    }
    else if (moveNum == 7) { // q move
        std::pair<int, int> wherePiece = findPiece('Q',0);
        board[wherePiece.first][wherePiece.second] = ' ';
        if (lengthMove == 3) {
            int file = findFile(move[1]);
            board[8 - (static_cast<int>(move[2]) - 48)][file] = 'Q';
        }
        if (lengthMove == 4) {
            int file = findFile(move[2]);
            board[8 - (static_cast<int>(move[3]) - 48)][file] = 'Q';
        }
    }
    else if (moveNum == 8) { // b move
        if (lengthMove == 3) {
            int file = findFile(move[1]);
            int colorBishop = file + (8 - (static_cast<int>(move[2]) - 48));
            std::pair<int, int> wherePiece = findPiece('B',colorBishop%2);
            board[wherePiece.first][wherePiece.second] = ' ';
            board[8 - (static_cast<int>(move[2]) - 48)][file] = 'B';
        }
        if (lengthMove == 4) {
            int file = findFile(move[2]);
            int colorBishop = file + (8 - (static_cast<int>(move[3]) - 48));
            std::pair<int, int> wherePiece = findPiece('B',colorBishop%2);
            board[wherePiece.first][wherePiece.second] = ' ';
            board[8 - (static_cast<int>(move[3]) - 48)][file] = 'B';
        }

    }
    else if (moveNum == 9) { // n move
        if (lengthMove == 5) {
            int file = findFile(move[0]);
            int row = findRow('N',file, 0);
            board[row][file] = ' ';
            board[8 - (static_cast<int>(move[3]) - 48)][findFile(move[4])] = 'N';
        }
        if (lengthMove == 4) {
                int file = findFile(move[1]);
                if (file == -1) {
                    int row = 8 - (static_cast<int>(move[1]) - 48);
                    for (int i = 0; i < 8; i++) {
                        if (board[row][i] == 'N') {
                            board[row][i] = ' ';
                            break;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (board[i][file] == 'N') {
                            board[i][file] = ' ';
                            break;
                        }
                    }
                }
                board[8 - (static_cast<int>(move[3]) - 48)][findFile(move[2])] = 'N';
      
        }
        if (lengthMove == 3) {
            int file = findFile(move[1]);
            int row = (8 - (static_cast<int>(move[2]) - 48));
            board[row][file] = 'N';
            if (board[row - 2][file + 1] == 'N') {
                board[row - 2][file + 1] = ' ';
            }
            if (board[row - 2][file - 1] == 'N') {
                board[row - 2][file - 1] = ' ';
            }
            if (board[row + 2][file + 1] == 'N') {
                board[row + 2][file + 1] = ' ';
            }
            if (board[row + 2][file - 1] == 'N') {
                board[row + 2][file - 1] = ' ';
            }
            if (board[row + 1][file + 2] == 'N') {
                board[row + 1][file + 2] = ' ';
            }
            if (board[row - 1][file + 2] == 'N') {
                board[row - 1][file + 2] = ' ';
            }
            if (board[row + 1][file - 2] == 'N') {
                board[row + 1][file - 2] = ' ';
            }
            if (board[row - 1][file - 2] == 'N') {
                board[row - 1][file - 2] = ' ';
            }
        }
    }
    else if (moveNum == 10) { // r move
        if (lengthMove == 5) {
            int file = findFile(move[1]);
            if (file == -1) {
                int row = 8 - (static_cast<int>(move[1]) - 48);
                for (int i = 0; i < 8; i++) {
                    if (board[row][i] == 'R') {
                        board[row][i] = ' ';
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    if (board[i][file] == 'R') {
                        board[i][file] = ' ';
                        break;
                    }
                }
            }
            board[8 - (static_cast<int>(move[4]) - 48)][findFile(move[3])] = 'R';
        }
        if (lengthMove == 4 && move[1] == 'x') {
            int file = findFile(move[2]);
            for (int i = 0; i < 8; i++) {
                if (board[i][file] == 'R') {
                    board[i][file] = ' ';
                    break;
                }
            }
            for (int i = 0; i < 8; i++) {
                if (board[8 - (static_cast<int>(move[3]) - 48)][i] == 'R') {
                    board[8 - (static_cast<int>(move[3]) - 48)][i] = ' ';
                    break;
                }
            }
            board[8 - (static_cast<int>(move[3]) - 48)][findFile(move[2])] = 'R';
        }
        if (lengthMove == 4 && move[1] != 'x') {
            int file = findFile(move[1]);
            if (file == -1) {
                int row = 8 - (static_cast<int>(move[1]) - 48);
                for (int i = 0; i < 8; i++) {
                    if (board[row][i] == 'R') {
                        board[row][i] = ' ';
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    if (board[i][file] == 'R') {
                        board[i][file] = ' ';
                        break;
                    }
                }
            }
            board[8 - (static_cast<int>(move[3]) - 48)][findFile(move[2])] = 'R';

        }
        if (lengthMove == 3) {
            int file = findFile(move[1]);
            for (int i = 0; i < 8; i++) {
                if (board[i][file] == 'R') {
                    board[i][file] = ' ';
                    break;
                }
            }
            board[8 - (static_cast<int>(move[2]) - 48)][findFile(move[1])] = 'R';
        }
    }
   
}

void bitBoard::botMove(){
    char testBoard[8][8] = {};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            testBoard[i][j] = board[i][j];
        }
    }
    std::vector<int> realMove;
    
    if (moveNumber < 6) {
        realMove = opening.at(moveNumber);
        moveNumber++;
    }
    else {
        std::vector<moves> moveList;
        std::vector<moves> incomingList;

        for (int row = 0; row < 8; row++) { // Finding all possible moves for black
            for (int col = 0; col < 8; col++) {
                if (islower(board[row][col])) {
                    //moveList.insert(moveList.end(),generateMoveForPiece(row, col,board,rookMove).begin(), generateMoveForPiece(row, col, board,rookMove).end());
                    incomingList = generateMoveForPiece(row, col, testBoard, rookMove);
                    moveList.insert(moveList.end(), incomingList.begin(), incomingList.end());
                }
            }
        }

        realMove = moveCords(moveSearch(moveList, testBoard)); //pick the move funtion here
        //for (auto e : moveList) {
        //    std::cout << e.row << " " << e.col << " " << e.tRow << " " << e.tRow << '\n';
        //}
    }
    for (auto e : realMove) {
        std::cout << e << " ";
    }
    std::cout << '\n';
    if (realMove.at(5) == 1) {
        board[0][0] = ' ';
        board[0][2] = 'r';
        board[0][3] = 'k';
        board[0][4] = ' ';
        return;
    }
    if (realMove.at(5) == 2) {
        board[0][4] = ' ';
        board[0][5] = 'r';
        board[0][6] = 'k';
        board[0][7] = ' ';
        return;
    }
    char character = board[realMove.at(0)][realMove.at(1)];
    board[realMove.at(0)][realMove.at(1)] = ' ';
    if (realMove.at(4) != 0) {
        char b[4] = { 'q','n','b','r' };
        character = b[realMove.at(4)];

    }
    board[realMove.at(2)][realMove.at(3)] = character;
}
bool bitBoard::whiteBlackTurn() {
    return 0;
}
void bitBoard::printBoard() {
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            std::cout << "[" << board[i][j] << "]";
        }
        std::cout << '\n';
    }
    std::cout << "   a  b  c  d  e  f  g  h" << '\n';
}