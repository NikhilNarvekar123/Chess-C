#pragma once
#include "AI.h"

// initializes AI to default difficulty 
AI::AI() {
	difficulty = 3;
}

// sets AI to given difficulty (2 -> easy, 3 -> regular, 4-> hard)
void AI::setDifficulty(int diff) {
	difficulty = diff;
}

/* given a board, the AI generates all possible moves for itself and then 
   calls the minmax function on each board with each possible move made. Returns
   the highest valued board out of them all.
*/
void AI::makeMove(Board &board, string aiColor) {

	// set AI and opponent color
	Color color = (aiColor == "black") ? Color::BLACK : Color::WHITE;
	Color otherColor = (aiColor == "black") ? Color::WHITE : Color::BLACK;

	// find all possible moves AI can make
	vector<Board> boardStates;
	boardStates = generateMoves(board, color);

	// simulate making each move and then call on minmax function for each simulated move
	// move with the highest
	int maxMoveVal = INT_MIN;
	Board bestBoardState;
	for (int i = 0; i < boardStates.size(); i++) {
		int val = runMinmax(boardStates[i], otherColor, 1, difficulty, INT_MIN, INT_MAX);
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
			int val = runMinmax(boardStates[i], Color::WHITE, curDepth + 1, difficulty, alpha, beta);
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
			int val = runMinmax(boardStates[i], Color::BLACK, curDepth + 1, difficulty, alpha, beta);
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
