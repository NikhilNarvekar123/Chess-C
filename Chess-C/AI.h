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
	vector<vector<vector<Piece>>> generateMoves(vector<vector<Piece>> boardState, Color color);
	vector<vector<Piece>> simulateMove(Point startPt, Point endpt, vector<vector<Piece>> board);
	int checkWin(vector<vector<Piece>> board);
	vector<int> returnValuation(vector<vector<Piece>> board);



private:
	int runMinmax(int player, vector<vector<Piece>> loopBoard, int curDepth, int maxDepth);
	
	vector<vector<Piece>> currentBoard;
	vector<vector<vector<Piece>>> boardStates;

	vector<vector<vector<Piece>>> rookMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	vector<vector<vector<Piece>>> knightMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	vector<vector<vector<Piece>>> bishopMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	vector<vector<vector<Piece>>> kingMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	vector<vector<vector<Piece>>> queenMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
	vector<vector<vector<Piece>>> pawnMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt);
};

