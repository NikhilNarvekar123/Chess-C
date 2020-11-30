#pragma once
#include "Piece.h";

// empty location
Piece::Piece() {
	piece = Type::EMPTY;
	color = Color::EMPTY;
	status = Status::EMPTY;
	curLocation = Point();
}

// creates a piece
Piece::Piece(Type piece, Color color) {
	this->piece = piece;
	this->color = color;
	status = Status::SPAWN;
}

// updates/retrieves location of piece
void Piece::setLocation(Point newLoc) {
	curLocation = newLoc;
}
Point Piece::getLocation() {
	return curLocation;
}

// returns display name of piece ('rb') and actual name
string Piece::returnBoardName() {
	string colorPostfix = "";
	if (color == Color::BLACK)
		colorPostfix = "b";
	else
		colorPostfix = "w";

	switch (piece) {
	case Type::ROOK:
		return "r" + colorPostfix;
	case Type::KNIGHT:
		return "h" + colorPostfix;
	case Type::BISHOP:
		return "b" + colorPostfix;
	case Type::KING:
		return "k" + colorPostfix;
	case Type::QUEEN:
		return "q" + colorPostfix;
	case Type::PAWN:
		return "p" + colorPostfix;
	default:
		return "  ";
	}
}
string Piece::returnName() {
	switch (piece) {
	case Type::ROOK:
		return "ROOK";
	case Type::KNIGHT:
		return "KNIGHT";
	case Type::BISHOP:
		return "BISHOP";
	case Type::KING:
		return "KING";
	case Type::QUEEN:
		return "QUEEN";
	case Type::PAWN:
		return "PAWN";
	default:
		return "EMPTY";
	}
}

// return piece type and color
Type Piece::returnType() {
	return this->piece;
}
Color Piece::returnColor() {
	return this->color;
}


bool Piece::rookMove(Point startPoint, Point endPoint, Board board) {

	bool firstCheck = false;

	if (abs(startPoint.row - endPoint.row) == 0)
		firstCheck = true;
	else if (abs(startPoint.col - endPoint.col) == 0)
		firstCheck = true;

	if (!firstCheck) {
		return false;
	}

	int rowDif = startPoint.row - endPoint.row;
	int colDif = startPoint.col - endPoint.col;

	//downward
	if (rowDif < 0) {
		for (int r = startPoint.row; r <= endPoint.row; r++) {
			Piece alongPiece = board[r][startPoint.col];

			if (alongPiece.returnType() != Type::EMPTY && r != endPoint.row) {
				return false;
			}
		}
	}
	//upward
	if (rowDif > 0) {
		for (int r = startPoint.row; r >= endPoint.row; r--) {
			Piece alongPiece = board[r][startPoint.col];
			if (alongPiece.returnType() != Type::EMPTY && r != endPoint.row) {
				return false;
			}
		}
	}
	//right
	if (colDif < 0) {
		for (int c = startPoint.col; c <= endPoint.col; c++) {
			Piece alongPiece = board[startPoint.row][c];
			if (alongPiece.returnType() != Type::EMPTY && c != endPoint.col) {
				return false;
			}
		}
	}
	//left
	if (colDif > 0) {
		for (int c = startPoint.col; c >= endPoint.col; c--) {
			Piece alongPiece = board[startPoint.row][c];
			if (alongPiece.returnType() != Type::EMPTY && c != endPoint.col) {
				return false;
			}
		}
	}
	return true;

}

bool Piece::knightMove(Point startPoint, Point endPoint, Board board) {

	bool firstCheck = false;
	if (abs(startPoint.row - endPoint.row) == 2 && abs(startPoint.col - endPoint.col) == 1)
		firstCheck = true;
	else if (abs(startPoint.row - endPoint.row) == 1 && abs(startPoint.col - endPoint.col) == 2)
		firstCheck = true;

	return firstCheck;
}

bool Piece::bishopMove(Point startPoint, Point endPoint, Board board) {

	bool firstCheck = false;
	if (abs(startPoint.row - endPoint.row) == abs(startPoint.col - endPoint.col))
		firstCheck = true;

	if (!firstCheck) {
		return false;
	}

	int rowDif = startPoint.row - endPoint.row;
	int colDif = startPoint.col - endPoint.col;

	//southeast
	if (rowDif < 0 && colDif < 0) {
		int c = startPoint.col;
		for (int r = startPoint.row; r <= endPoint.row; r++) {
			Piece alongPiece = board[r][c];
			if (alongPiece.returnType() != Type::EMPTY && r != endPoint.row) {
				return false;
			}
			c++;
		}
	}
	//southwest
	if (rowDif < 0 && colDif > 0) {
		int c = startPoint.col;
		for (int r = startPoint.row; r <= endPoint.row; r++) {
			Piece alongPiece = board[r][c];
			if (alongPiece.returnType() != Type::EMPTY && r != endPoint.row) {
				return false;
			}
			c--;
		}
	}
	//northeast
	if (rowDif > 0 && colDif < 0) {
		int c = startPoint.col;
		for (int r = startPoint.row; r >= endPoint.row; r--) {
			Piece alongPiece = board[r][c];
			if (alongPiece.returnType() != Type::EMPTY && r != endPoint.row) {
				return false;
			}
			c++;
		}
	}
	//northwest
	if (rowDif > 0 && colDif > 0) {
		int c = startPoint.col;
		for (int r = startPoint.row; r >= endPoint.row; r--) {
			Piece alongPiece = board[r][c];
			if (alongPiece.returnType() != Type::EMPTY && r != endPoint.row) {
				return false;
			}
			c--;
		}
	}

	return true;
}

bool Piece::kingMove(Point startPoint, Point endPoint, Board board) {

	bool firstCheck = false;
	if (abs(startPoint.row - endPoint.row) <= 1 && abs(startPoint.col - endPoint.col) <= 1)
		firstCheck = true;

	return firstCheck;
}

bool Piece::queenMove(Point startPoint, Point endPoint, Board board) {

	bool firstCheck = bishopMove(startPoint, endPoint);
	if (firstCheck == false)
		firstCheck = rookMove(startPoint, endPoint);

	return firstCheck;
}

bool Piece::pawnMove(Point startPoint, Point endPoint, Board board) {

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
			if (board[endPoint.row][endPoint.col].returnType() != Type::EMPTY) {
				status = Status::INGAME;
				return true;
			}
			else
				return false;
		}

		// As long as space moving to is empty (and in same row)
		if (board[endPoint.row][endPoint.col].returnType() == Type::EMPTY) {
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
