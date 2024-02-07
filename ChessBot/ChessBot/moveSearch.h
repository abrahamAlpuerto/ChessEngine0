#pragma once
#include"moveGeneration.h"
using namespace moveGeneration;

extern enum Pieces {
	PAWN = 1, BISHOP = 3, ROOK = 5,
	KNIGHT = 3, KING = 1000, QUEEN = 9
};


extern moves moveSearch(std::vector<moves> moveList,char bB[8][8]);
extern int tradeValue(moves moveList, char bB[8][8]);
extern int position(moves moveList, char bB[8][8]);