#include "AI.h"


Move AI::makeMove(vector<vector<Piece>> boardState) {
	generateMoves(boardState);
	int moveNum = rand() % moveList.size();
	return moveList[moveNum];
}


void AI::generateMoves(vector<vector<Piece>> boardState) {

	this->boardState = boardState;
	for (int r = 0; r < 8; r++) {
		
		for (int c = 0; c < 8; c++) {

			Piece curPiece = boardState[r][c];
			
			if (curPiece.returnColor() != Color::BLACK && curPiece.returnPieceType() != PieceType::EMPTY) {
				continue;
			}

			PieceType piece = curPiece.returnPieceType();

			if (piece == PieceType::ROOK)
				rookMoves(curPiece);
			else if (piece == PieceType::KNIGHT)
				knightMoves(curPiece);
			else if (piece == PieceType::BISHOP)
				bishopMoves(curPiece);
			else if (piece == PieceType::KING)
				kingMoves(curPiece);
			else if (piece == PieceType::QUEEN)
				queenMoves(curPiece);
			else if (piece == PieceType::PAWN)
				pawnMoves(curPiece);

		}
	}



}

void AI::rookMoves(Piece curPiece) {

	// adding all valid moves in current column
	for (int r = 0; r < 8; r++) {

		Point startPt = curPiece.returnLocation();
		Point endPt;
		endPt.row = r;
		endPt.col = startPt.col;

		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if(startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
	}

	// adding all valid moves in current row
	for (int c = 0; c < 8; c++) {

		Point startPt = curPiece.returnLocation();
		Point endPt;
		endPt.row = c;
		endPt.col = startPt.row;

		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
	}

}

void AI::knightMoves(Piece curPiece) {
	
	Point startPt = curPiece.returnLocation();
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
		if (curPiece.movePiece(startPt, validEndpts[i], boardState, 2)) {
			if (startPt.row != validEndpts[i].row && startPt.col != validEndpts[i].col)
				moveList.push_back(Move(startPt, validEndpts[i]));
		}
	}

}

void AI::bishopMoves(Piece curPiece) {

	Point startPt = curPiece.returnLocation();
	Point endPt(startPt.row, startPt.col);


	// northwest
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
		endPt.row -= 1;
		endPt.col -= 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;
	
	// southeast
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
		endPt.row += 1;
		endPt.col += 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;

	// northeast
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
		endPt.row -= 1;
		endPt.col += 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;

	// southwest
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
		endPt.row += 1;
		endPt.col -= 1;
	}


}

void AI::queenMoves(Piece curPiece) {

	bishopMoves(curPiece);
	rookMoves(curPiece);


}

void AI::kingMoves(Piece curPiece) {

	Point startPt = curPiece.returnLocation();
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
		if (curPiece.movePiece(startPt, validEndpts[i], boardState, 2)) {
			if (startPt.row != validEndpts[i].row && startPt.col != validEndpts[i].col)
				moveList.push_back(Move(startPt, validEndpts[i]));
		}
	}

}

void AI::pawnMoves(Piece curPiece) {

	Point startPt = curPiece.returnLocation();

	for (int r = 0; r < 8; r++) {
		Point endPt(r, startPt.col);
		if (curPiece.movePiece(startPt, endPt, boardState, 2)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				moveList.push_back(Move(startPt, endPt));
		}
	}

}