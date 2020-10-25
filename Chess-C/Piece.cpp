#pragma once
#include "Piece.h";

Piece::Piece() {
	piece = PieceType::EMPTY;
	color = Color::EMPTY;
	status = Status::EMPTY;
}

Piece::Piece(PieceType piece, Color color) {
	this->piece = piece;
	this->color = color;
	status = Status::SPAWN;
}

string Piece::returnBoardName() {
	string colorPostfix = "";
	if (color == Color::BLACK)
		colorPostfix = "b";
	else
		colorPostfix = "w";

	switch (piece) {
		case PieceType::ROOK:
			return "r" + colorPostfix;
		case PieceType::KNIGHT:
			return "h" + colorPostfix;
		case PieceType::BISHOP:
			return "b" + colorPostfix;
		case PieceType::KING:
			return "k" + colorPostfix;
		case PieceType::QUEEN:
			return "q" + colorPostfix;
		case PieceType::PAWN:
			return "p" + colorPostfix;
		default:
			return "  ";
	}
}

string Piece::returnName() {
	switch (piece) {
	case PieceType::ROOK:
		return "ROOK";
	case PieceType::KNIGHT:
		return "KNIGHT";
	case PieceType::BISHOP:
		return "BISHOP";
	case PieceType::KING:
		return "KING";
	case PieceType::QUEEN:
		return "QUEEN";
	case PieceType::PAWN:
		return "PAWN";
	default:
		return "EMPTY";
	}
}

void Piece::updateLocation(Point newLoc) {
	this->location = newLoc;
}

Point Piece::returnLocation() {
	return this->location;
}

Color Piece::returnColor() {
	return this->color;
}

PieceType Piece::returnPieceType() {
	return this->piece;
}

bool Piece::checkBounds(Point p) {

	// If end or start point out of grid, notify main method
	if (!(p.row >= 0 && p.row <= 7))
		return false;
	if (!(p.col >= 0 && p.col <= 7))
		return false;

}

bool Piece::movePiece(Point startPoint, Point endPoint, vector<vector<Piece>> boardCopy, int playerID) {
	
	this->startPoint = startPoint;
	this->endPoint = endPoint;
	this->boardCopy = boardCopy;

	if (playerID == 1 && this->color != Color::WHITE)
		return false;
	if (playerID == 2 && this->color != Color::BLACK)
		return false;

	if (!checkBounds(startPoint) || !checkBounds(endPoint))
		return false;

	//break apart into separate methods to handle movement validation
	if (piece == PieceType::ROOK)
		return rookMove();
	else if (piece == PieceType::KNIGHT)
		return knightMove();
	else if (piece == PieceType::BISHOP)
		return bishopMove();
	else if (piece == PieceType::KING)
		return kingMove();
	else if (piece == PieceType::QUEEN)
		return queenMove();
	else if (piece == PieceType::PAWN)
		return pawnMove();
	else
		return false; 
}

bool Piece::rookMove() {

	bool firstCheck = false;
	
	if (abs(startPoint.row - endPoint.row) == 0)
		firstCheck = true;
	else if(abs(startPoint.col - endPoint.col) == 0)
		firstCheck = true;
	
	if (!firstCheck) {
		return false;
	} 
	else {
	
		int rowDif = startPoint.row - endPoint.row;
		int colDif = startPoint.col - endPoint.col;

		//downward
		if (rowDif < 0) {
			for (int r = startPoint.row; r <= endPoint.row; r++) {
				Piece alongPiece = boardCopy[r][startPoint.col];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					return false;
				}
			}
		}
		//upward
		if (rowDif > 0) {
			for (int r = startPoint.row; r >= endPoint.row; r--) {
				Piece alongPiece = boardCopy[r][startPoint.col];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					return false;
				}
			}
		}
		//right
		if (colDif < 0) {
			for (int c = startPoint.col; c <= endPoint.col; c++) {
				Piece alongPiece = boardCopy[startPoint.row][c];
				if (alongPiece.returnName() != "EMPTY" && c != endPoint.col) {
					return false;
				}
			}
		}
		//left
		if (colDif > 0) {
			for (int c = startPoint.col; c >= endPoint.col; c--) {
				Piece alongPiece = boardCopy[startPoint.row][c];
				if (alongPiece.returnName() != "EMPTY" && c != endPoint.col) {
					return false;
				}
			}
		}

		return true;
	}
}

bool Piece::knightMove() {

	bool firstCheck = false;
	if (abs(startPoint.row - endPoint.row) == 2 && abs(startPoint.col - endPoint.col) == 1)
		firstCheck = true;
	else if (abs(startPoint.row - endPoint.row) == 1 && abs(startPoint.col - endPoint.col) == 2)
		firstCheck = true;		

	return firstCheck;
}

bool Piece::bishopMove() {

	bool firstCheck = false;
	if (abs(startPoint.row - endPoint.row) == abs(startPoint.col - endPoint.col))
		firstCheck = true;

	if (!firstCheck) {
		return false;
	}
	else {

		int rowDif = startPoint.row - endPoint.row;
		int colDif = startPoint.col - endPoint.col;

		//southeast
		if (rowDif < 0 && colDif < 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r <= endPoint.row; r++) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					return false;
				}
				c++;
			}
		}
		//southwest
		if (rowDif < 0 && colDif > 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r <= endPoint.row; r++) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					return false;
				}
				c--;
			}
		}
		//northeast
		if (rowDif > 0 && colDif < 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r >= endPoint.row; r--) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					return false;
				}
				c++;
			}
		}
		//northwest
		if (rowDif > 0 && colDif > 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r >= endPoint.row; r--) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					return false;
				}
				c--;
			}
		}

		return true;
	}
}

bool Piece::kingMove() {

	bool firstCheck = false;
	if (abs(startPoint.row - endPoint.row) <= 1 && abs(startPoint.col - endPoint.col) <= 1)
		firstCheck = true;

	return firstCheck;
}

bool Piece::queenMove() {

	bool firstCheck = bishopMove();
	if (firstCheck == false)
		firstCheck = rookMove();
	
	return firstCheck;
}

bool Piece::pawnMove() {

	bool firstCheck;
	int rowDif = startPoint.row - endPoint.row;
	int colDif = startPoint.col - endPoint.col;

	// If moving columns without taking piece, return false
	if (colDif != 0 && abs(colDif) != 1)
		return false;

	// If moving in opposite direction of color, return false
	if (color == Color::BLACK && !(rowDif < 0))
		return false;
	if (color == Color::WHITE && !(rowDif > 0))
		return false;

	// If moving 1 space up/down
	if (abs(rowDif) == 1) {
		
		status = Status::INGAME;
		
		// If taking piece, then has to be non-empty space
		if (abs(colDif) == 1) {
			if (boardCopy[endPoint.row][endPoint.col].returnName() != "EMPTY") {
				status = Status::INGAME;
				return true;
			}
			else
				return false;
		}
		
		// As long as space moving to is empty (and in same row)
		if (boardCopy[endPoint.row][endPoint.col].returnName() == "EMPTY") {
			status = Status::INGAME;
			return true;
		}
		
	}
	else if (abs(rowDif) == 2) {
		// If spawn piece, moving two squares ahead is allowed
		if (status == Status::SPAWN) {
			status = Status::INGAME;
			return true;
		}
	}

	return false;
}