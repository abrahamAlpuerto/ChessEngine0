#include"moveGeneration.h"

namespace moveGeneration {


    std::vector<moves> generateMoveForPiece(int row, int col, char bB[8][8],bool castleMove[3]) {
        char piece = bB[row][col];
        std::vector<moves> pieceMoves;
        moves newMove;
        newMove.row = row;
        newMove.col = col;

        if (piece == 'p') { //PAWNS
            if (row == 1 && bB[2][col] == ' ' && bB[3][col] == ' ') {
                newMove.tRow = 3;
                newMove.tCol = col;
                pieceMoves.push_back(newMove);
            }
            if (bB[row + 1][col] == ' ') {
                newMove.tRow = row + 1;
                newMove.tCol = col;
                pieceMoves.push_back(newMove);
            }
            if (isupper(bB[row + 1][col + 1]) && bB[row + 1][col + 1] != '\0' && col + 1 >= 0 && col + 1 < 8) {
                newMove.tRow = row + 1;
                newMove.tCol = col + 1;
                pieceMoves.push_back(newMove);
            }
            if (isupper(bB[row + 1][col - 1]) && bB[row + 1][col + 1] != '\0' && col - 1 >= 0 && col - 1 < 8) {
                newMove.tRow = row + 1;
                newMove.tCol = col - 1;
                pieceMoves.push_back(newMove);
            }
            if (bB[row + 1][col] == ' ' && row + 1 == 7) {
                newMove.tRow = row + 1;
                newMove.tCol = col;
                newMove.promo = 1;
                pieceMoves.push_back(newMove);
                newMove.promo = 2;
                pieceMoves.push_back(newMove);
                newMove.promo = 3;
                pieceMoves.push_back(newMove);
                newMove.promo = 4;
                pieceMoves.push_back(newMove);
            }
        }
        else if (piece == 'k') { // KING
            if (row + 1 >= 0 && row + 1 < 8) {
                if (bB[row + 1][col] == ' ' || isupper(bB[row + 1][col])) {
                    newMove.tRow = row + 1;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row - 1 >= 0 && row - 1 < 8) {
                if (bB[row - 1][col] == ' ' || isupper(bB[row - 1][col])) {
                    newMove.tRow = row - 1;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                }
            }
            if (col + 1 >= 0 && col + 1 < 8) {
                if (bB[row][col + 1] == ' ' || isupper(bB[row][col + 1])) {
                    newMove.tRow = row;
                    newMove.tCol = col + 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (col - 1 >= 0 && col - 1 < 8) {
                if (bB[row][col - 1] == ' ' || isupper(bB[row][col - 1])) {
                    newMove.tRow = row;
                    newMove.tCol = col - 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row + 1 >= 0 && row + 1 < 8 && col + 1 >= 0 && col + 1 < 8) {
                if (bB[row + 1][col + 1] == ' ' || isupper(bB[row][col - 1])) {
                    newMove.tRow = row + 1;
                    newMove.tCol = col + 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row - 1 >= 0 && row - 1 < 8 && col + 1 >= 0 && col + 1 < 8) {
                if (bB[row - 1][col + 1] == ' ' || isupper(bB[row][col - 1])) {
                    newMove.tRow = row - 1;
                    newMove.tCol = col + 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row + 1 >= 0 && row + 1 < 8 && col - 1 >= 0 && col - 1 < 8) {
                if (bB[row + 1][col - 1] == ' ' || isupper(bB[row][col - 1])) {
                    newMove.tRow = row + 1;
                    newMove.tCol = col - 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row - 1 >= 0 && row - 1 < 8 && col - 1 >= 0 && col - 1 < 8) {
                if (bB[row - 1][col - 1] == ' ' || isupper(bB[row][col - 1])) {
                    newMove.tRow = row - 1;
                    newMove.tCol = col - 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (castleMove[0] == 0 && castleMove[2] == 0 && bB[0][1] == ' ' && bB[0][2] == ' ' && bB[0][3] == ' ') {
                newMove.tRow = 0;
                newMove.tCol = 2;
                newMove.castle = 1;
                pieceMoves.push_back(newMove);
            }
            if (castleMove[1] == 0 && castleMove[2] == 0 && bB[0][5] == ' ' && bB[0][6] == ' ') {
                newMove.castle = 2;
                newMove.tRow = 0;
                newMove.tCol = 6;
                pieceMoves.push_back(newMove);
            }
        }
        else if (piece == 'q') { // QUEEN
            for (int i = 1; i < 8 && row + i < 8; i++) {
                if (bB[row + i][col] == ' ' && col + 1 >= 0 && col + 1 < 8) {
                    newMove.tRow = row + i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row + i][col])) {
                    newMove.tRow = row + i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row - i >= 0; i++) {
                if (bB[row - i][col] == ' ' && col + 1 >= 0 && col + 1 < 8) {
                    newMove.tRow = row - i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row - i][col])) {
                    newMove.tRow = row - i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && col + i < 8; i++) {
                if (bB[row][col + i] == ' ' && col + 1 >= 0 && col + 1 < 8) {
                    newMove.tRow = row;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row][col + i])) {
                    newMove.tRow = row;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && col - i >= 0; i++) {
                if (bB[row][col - i] == ' ') {
                    newMove.tRow = row;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row ][col - i])) {
                    newMove.tRow = row;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row - i >= 0 && col - i >= 0; i++) {
                if (bB[row - i][col - i] == ' ') {
                    newMove.tRow = row - i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row - i][col - i])) {
                    newMove.tRow = row - i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row + i < 8 && col - i >= 0; i++) {
                if (bB[row + i][col - i] == ' ') {
                    newMove.tRow = row + i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row + i][col - i])) {
                    newMove.tRow = row + i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row + i < 8 && col + i < 8; i++) {
                if (bB[row + i][col + i] == ' ') {
                    newMove.tRow = row + i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row + i][col + i])) {
                    newMove.tRow = row + i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row - i >= 0 && col + i < 8; i++) {
                if (bB[row - i][col + i] == ' ') {
                    newMove.tRow = row - i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row - i][col + i])) {
                    newMove.tRow = row - i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else if (piece == 'b') { //BISHOPS
            for (int i = 1; i < 8 && row - i >= 0 && col - i >=0; i++) {
                if (bB[row - i][col - i] == ' ') {
                    newMove.tRow = row - i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row - i][col - i])) {
                    newMove.tRow = row - i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row + i < 8 && col - i >= 0; i++) {
                if (bB[row + i][col - i] == ' ') {
                    newMove.tRow = row + i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row + i][col - i])) {
                    newMove.tRow = row + i;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row + i < 8 && col + i < 8; i++) {
                if (bB[row + i][col + i] == ' ') {
                    newMove.tRow = row + i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row + i][col + i])) {
                    newMove.tRow = row + i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row - i >= 0 && col + i < 8; i++) {
                if (bB[row - i][col + i] == ' ') {
                    newMove.tRow = row - i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row - i][col + i])) {
                    newMove.tRow = row - i;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else if (piece == 'n') { //KNIGHTS
            if (row - 2 >= 0 && row -2  < 8 && col + 1 >= 0 && col + 1 < 8) {
                if (bB[row - 2][col + 1] == ' ' || isupper(bB[row - 2][col + 1])) {
                    newMove.tRow = row - 2;
                    newMove.tCol = col + 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row + 2 >= 0 && row + 2 < 8 && col + 1 >= 0 && col + 1 < 8) {
                if (bB[row + 2][col + 1] == ' ' || isupper(bB[row + 2][col + 1])) {
                    newMove.tRow = row + 2;
                    newMove.tCol = col + 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row - 2 >= 0 && row - 2 < 8 && col - 1 >= 0 && col - 1 < 8) {
                if (bB[row - 2][col - 1] == ' ' || isupper(bB[row - 2][col - 1])) {
                    newMove.tRow = row - 2;
                    newMove.tCol = col - 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row + 2 >= 0 && row + 2 < 8 && col - 1 >= 0 && col - 1 < 8) {
                if (bB[row + 2][col - 1] == ' ' || isupper(bB[row + 2][col - 1])) {
                    newMove.tRow = row + 2;
                    newMove.tCol = col - 1;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row + 1 >= 0 && row + 1 < 8 && col + 2 >= 0 && col + 2 < 8) {
                if (bB[row + 1][col + 2] == ' ' || isupper(bB[row + 1][col + 2])) {
                    newMove.tRow = row + 1;
                    newMove.tCol = col + 2;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row - 1 >= 0 && row - 1 < 8 && col + 2 >= 0 && col + 2 < 8) {
                if (bB[row - 1][col + 2] == ' ' || isupper(bB[row - 1][col + 2])) {
                    newMove.tRow = row - 1;
                    newMove.tCol = col + 2;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row + 1 >= 0 && row + 1 < 8 && col - 2 >= 0 && col - 2 < 8) {
                if (bB[row + 1][col - 2] == ' ' || isupper(bB[row + 1][col - 2])) {
                    newMove.tRow = row + 1;
                    newMove.tCol = col - 2;
                    pieceMoves.push_back(newMove);
                }
            }
            if (row - 1 >= 0 && row - 1 < 8 && col - 2 >= 0 && col - 2 < 8) {
                if (bB[row - 1][col - 2] == ' ' || isupper(bB[row - 1][col - 2])) {
                    newMove.tRow = row - 1;
                    newMove.tCol = col - 2;
                    pieceMoves.push_back(newMove);
                }
            }
        }
        else if (piece == 'r') { //ROOKS
            for (int i = 1; i < 8 && row + i < 8; i++) {
                if (bB[row + i][col] == ' ' && col + 1 >= 0 && col + 1 < 8) {
                    newMove.tRow = row + i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row + i][col])) {
                    newMove.tRow = row + i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && row - i >= 0; i++) {
                if (bB[row - i][col] == ' ' && col + 1 >= 0 && col + 1 < 8) {
                    newMove.tRow = row - i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row - i][col])) {
                    newMove.tRow = row - i;
                    newMove.tCol = col;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && col + i < 8; i++) {
                if (bB[row][col + i] == ' ' && col + 1 >= 0 && col + 1 < 8) {
                    newMove.tRow = row;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row][col + i])) {
                    newMove.tRow = row;
                    newMove.tCol = col + i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i < 8 && col - i >= 0; i++) {
                if (bB[row][col - i] == ' ') {
                    newMove.tRow = row;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                }
                else if (std::isupper(bB[row][col - i])) {
                    newMove.tRow = row;
                    newMove.tCol = col - i;
                    pieceMoves.push_back(newMove);
                    break;
                }
                else {
                    break;
                }
            }
        }
        return pieceMoves;
    }

    std::vector<int> moveCords(moves move) {
        std::vector<int> a;

        a.push_back(move.row);
        a.push_back(move.col);
        a.push_back(move.tRow);
        a.push_back(move.tCol);
        a.push_back(move.promo);
        a.push_back(move.castle);
        return a;
    }
}