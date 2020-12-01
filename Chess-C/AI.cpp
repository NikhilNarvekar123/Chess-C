#pragma once
#include "AI.h"


void AI::makeMove(Board &board, string aiColor) {

	Color color = (aiColor == "black") ? Color::BLACK : Color::WHITE;

	vector<Board> boardStates;
	boardStates = generateMoves(board, color);

	int maxMoveVal = INT_MIN;
	Board bestBoardState;
	for (int i = 0; i < boardStates.size(); i++) {
		//minmax
	}

	board.setBoard(bestBoardState.returnBoard());
}


vector<Board> AI::generateMoves(Board board, Color color) {
	
	vector<Board> boardStates;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece piece = board.getPiece(r, c);
			
			if (piece.returnColor() == color) {
				vector<Point> pieceMoves = piece.generateMoves(board);
				for (Point pieceMove : pieceMoves) {
					Board newBoard;
					newBoard.setBoard(board.returnBoard());
					newBoard.movePiece(Point(r, c), pieceMove, color);
					boardStates.push_back(newBoard);
				}
			}
		}
	}

	return boardStates;
}


int AI::runMinmax(Board loopboard, Color player, int curDepth, int maxDepth) {
	return 0;
}


vector<int> AI::returnValuation(Board board) {

	int blackCount = 0;
	int whiteCount = 0;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.getPiece(r, c).returnColor() == Color::BLACK)
				blackCount++;
			else if (board.getPiece(r,c).returnColor() == Color::WHITE)
				whiteCount++;
		}
	}
	
	vector<int> values;
	values.push_back(blackCount * 5);
	values.push_back(whiteCount * 5);

	return values;
}
