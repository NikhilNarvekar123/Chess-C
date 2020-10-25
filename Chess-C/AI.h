#pragma once
#include <iostream>
#include "Common.h"
#include <vector>
#include <string>
#include "Piece.h"
#include <stdlib.h>

using namespace std;

class AI {


public:

	Move makeMove(vector<vector<Piece>> boardState);
	void generateMoves(vector<vector<Piece>> boardState);





private:
	vector<vector<Piece>> boardState;
	vector<Move> moveList;

	void rookMoves(Piece curPiece);
	void knightMoves(Piece curPiece);
	void bishopMoves(Piece curPiece);
	void kingMoves(Piece curPiece);
	void queenMoves(Piece curPiece);
	void pawnMoves(Piece curPiece);


};

