#pragma once
#include <iostream>
#include "Common.h"
#include <vector>
#include <string>
#include "Piece.h"
#include "Board.h"
#include <stdlib.h>

using namespace std;

class AI {


public:

	vector<vector<Piece>> makeMove(vector<vector<Piece>> boardState);
	void generateMoves(vector<vector<Piece>> boardState);
	void simulateMove(Point startPt, Point endpt, vector<vector<Piece>> board);




private:
	int runMinmax(int player, vector<vector<Piece>> loopBoard);
	
	vector<vector<Piece>> currentBoard;
	vector<vector<vector<Piece>>> boardStates;

	void rookMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	void knightMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	void bishopMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	void kingMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	void queenMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	void pawnMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
};

