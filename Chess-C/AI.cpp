#include "AI.h"

void AI::simulateMove(Point startPt, Point endpt, vector<vector<Piece>> board) {
	Piece startPiece = board[startPt.row][startPt.col];
	Piece endPiece = board[endpt.row][endpt.col];

	if (endPiece.returnType() == Type::EMPTY) {
		// If valid move to empty location, transfer board locations and output results
		board[endpt.row][endpt.col] = startPiece;
		board[startPt.row][startPt.col] = Piece();
	}
	else if (endPiece.returnType() != Type::EMPTY) {
		// If valid move to filled location, transfer board locations and output results
		board[endpt.row][endpt.col] = startPiece;
		board[startPt.row][startPt.col] = Piece();
	}
	boardStates.push_back(board);
}

vector<vector<Piece>> AI::makeMove(vector<vector<Piece>> boardState) {
	
	generateMoves(boardState);
	int maxMoveVal = INT_MIN;
	vector<vector<Piece>> bestBoardState;
	for (int i = 0; i < boardStates.size(); i++) {
		int value = runMinmax(2, boardStates[i]);
		if (value > maxMoveVal) {
			maxMoveVal = value;
			bestBoardState = boardStates[i];
		}
	}

	return bestBoardState;
}


int AI::runMinmax(int player, vector<vector<Piece>> loopBoard) {

	//minmax magic




}


void AI::generateMoves(vector<vector<Piece>> boardState) {
	
	// fills in all possible moves for board
	this->currentBoard = boardState;

	boardStates = {};
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece piece = boardState[r][c];
			Point curLocation;
			curLocation.row = r;
			curLocation.col = c;
			if (piece.returnColor() == Color::BLACK) {
				if (piece.returnType() == Type::BISHOP)
					bishopMoves(currentBoard, piece, curLocation);
				if (piece.returnType() == Type::ROOK)
					rookMoves(currentBoard, piece, curLocation);
				if (piece.returnType() == Type::KING)
					kingMoves(currentBoard, piece, curLocation);
				if (piece.returnType() == Type::QUEEN)
					queenMoves(currentBoard, piece, curLocation);
				if (piece.returnType() == Type::KNIGHT)
					knightMoves(currentBoard, piece, curLocation);
				if (piece.returnType() == Type::PAWN)
					pawnMoves(currentBoard, piece, curLocation);
			}
		}
	}
}



vector<vector<Piece>> AI::rookMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	// adding all valid moves in current column
	for (int r = 0; r < 8; r++) {

		Point endPt;
		endPt.row = r;
		endPt.col = startPt.col;

		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col){
				simulateMove(startPt, endPt, boardState);
			}
		}
	}

	// adding all valid moves in current row
	for (int c = 0; c < 8; c++) {
		Point endPt;
		endPt.row = c;
		endPt.col = startPt.row;

		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				simulateMove(startPt, endPt, boardState);
		}
	}

}

vector<vector<Piece>> AI::knightMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {
	
	vector<Point> validEndpts;

	validEndpts.push_back(Point(startPt.row + 2, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row + 2, startPt.col - 1));
	validEndpts.push_back(Point(startPt.row - 2, startPt.col - 1));
	validEndpts.push_back(Point(startPt.row - 2, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col - 2));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col + 2));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col - 2));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col + 2));

	for (int i = 0; i < validEndpts.size(); i++) {
		if (curPiece.movePiece(startPt, validEndpts[i], boardState)) {
			if (startPt.row != validEndpts[i].row && startPt.col != validEndpts[i].col)
				simulateMove(startPt, validEndpts[i], boardState);
		}
	}

}


vector<vector<Piece>> AI::bishopMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	Point endPt(startPt.row, startPt.col);


	// northwest
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				simulateMove(startPt, endPt, boardState);
		}
		endPt.row -= 1;
		endPt.col -= 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;
	
	// southeast
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				simulateMove(startPt, endPt, boardState);
		}
		endPt.row += 1;
		endPt.col += 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;

	// northeast
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				simulateMove(startPt, endPt, boardState);
		}
		endPt.row -= 1;
		endPt.col += 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;

	// southwest
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				simulateMove(startPt, endPt, boardState);
		}
		endPt.row += 1;
		endPt.col -= 1;
	}


}

vector<vector<Piece>> AI::queenMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	bishopMoves(boardState, curPiece, startPt);
	rookMoves(boardState, curPiece, startPt);

}

vector<vector<Piece>> AI::kingMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	vector<Point> validEndpts;

	validEndpts.push_back(Point(startPt.row + 1, startPt.col));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col));
	validEndpts.push_back(Point(startPt.row, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row, startPt.col - 1));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col + 2));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col - 2));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col - 2));

	for (int i = 0; i < validEndpts.size(); i++) {
		if (curPiece.movePiece(startPt, validEndpts[i], boardState)) {
			if (startPt.row != validEndpts[i].row && startPt.col != validEndpts[i].col)
				simulateMove(startPt, validEndpts[i], boardState);
		}
	}

}

vector<vector<Piece>> AI::pawnMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	for (int r = 0; r < 8; r++) {
		Point endPt(r, startPt.col);
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				simulateMove(startPt, endPt, boardState);
		}
	}

}