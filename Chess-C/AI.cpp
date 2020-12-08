#pragma once
#include "AI.h"


void AI::makeMove(Board &board, string aiColor) {

	Color color = (aiColor == "black") ? Color::BLACK : Color::WHITE;
	Color otherColor = (aiColor == "black") ? Color::WHITE : Color::BLACK;

	vector<Board> boardStates;
	boardStates = generateMoves(board, color);

	int maxMoveVal = INT_MIN;
	Board bestBoardState;
	for (int i = 0; i < boardStates.size(); i++) {
		int val = runMinmax(boardStates[i], otherColor, 1, 3, INT_MIN, INT_MAX);
		if (val > maxMoveVal) {
			maxMoveVal = val;
			bestBoardState = boardStates[i];
		}
	}
	board.setBoard(bestBoardState.returnBoard());
}


vector<Board> AI::generateMoves(Board board, Color color) {

	vector<Board> boardStates;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece piece = board.getPiece(r, c);

			if (piece.getColor() == color) {
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


int AI::runMinmax(Board loopboard, Color player, int curDepth, int maxDepth, int alpha, int beta) {

	if (curDepth == maxDepth) {
		return returnValuation(loopboard);
	}
	if (loopboard.checkWin() != Color::EMPTY) {
		return returnValuation(loopboard);
	}

	if (player == Color::BLACK) {

		vector<Board> boardStates;
		boardStates = generateMoves(loopboard, player);

		int maxMoveVal = INT_MIN;
		for (int i = 0; i < boardStates.size(); i++) {
			int val = runMinmax(boardStates[i], Color::WHITE, curDepth + 1, 3, alpha, beta);
			maxMoveVal = max(val, maxMoveVal);
			alpha = max(alpha, maxMoveVal);
			if(beta <= alpha)
				break;
		}
		return maxMoveVal;

	}
	else if (player == Color::WHITE) {

		vector<Board> boardStates;
		boardStates = generateMoves(loopboard, player);

		int minMoveVal = INT_MAX;
		for (int i = 0; i < boardStates.size(); i++) {
			int val = runMinmax(boardStates[i], Color::BLACK, curDepth + 1, 3, alpha, beta);
			minMoveVal = min(val, minMoveVal);
			beta = min(beta, minMoveVal);
			if(beta <= alpha)
				break;
		}

		return minMoveVal;
	}

}


int AI::returnValuation(Board board) {

	int blackCount = 0;
	int whiteCount = 0;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece curPiece = board.getPiece(r,c);
			if(curPiece.getColor() == Color::WHITE)
				whiteCount += curPiece.getValue();
			else
				blackCount += curPiece.getValue();
		}
	}

	Color winner = board.checkWin();
	if(winner == Color::BLACK)
		blackCount *= 100;
	if (winner == Color::WHITE)
		whiteCount *= 100;

	return blackCount - whiteCount;
}
