#include "Board_Piece.h";

// empty location
Piece::Piece() {
	piece = Type::EMPTY;
	color = Color::EMPTY;
	status = Status::EMPTY;
	curLocation = Point();
	valid = true;
}

// creates a piece
Piece::Piece(Type piece, Color color) {
	this->piece = piece;
	this->color = color;
	status = Status::SPAWN;
	valid = true;
}

Piece::Piece(int error) {
	valid = false;
}

bool Piece::isValid() {
	return valid;
}

// updates/retrieves location of piece
void Piece::setLocation(Point newLoc) {
	curLocation = newLoc;
}
Point Piece::getLocation() {
	return curLocation;
}

void Piece::setStatus(Status newStatus) {
	status = newStatus;
}
Status Piece::getStatus() {
	return status;
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


vector<Point> Piece::generateMoves(Board board) {

	vector<Point> validMoves;

	switch (piece) {
	case Type::ROOK:
		validMoves = rookMovesGen(board);
	case Type::KNIGHT:
		validMoves = knightMovesGen(board);
	case Type::BISHOP:
		validMoves = bishopMovesGen(board);
	case Type::KING:
		validMoves = kingMovesGen(board);
	case Type::QUEEN:
		validMoves = queenMovesGen(board);
	case Type::PAWN:
		validMoves = pawnMovesGen(board);
	default:
		validMoves = {};
	}

	return validMoves;

}

vector<Point> Piece::rookMovesGen(Board board) {

	vector<Point> validMoves;

	int curRow = curLocation.row;
	int curCol = curLocation.col;

	for (int r = curRow + 1; r < 8; r++) {
		Piece otherPiece = board.getPiece(r, curCol);
		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(r, curCol));
				break;
			}
		}
		else {
			validMoves.push_back(Point(r, curCol));
		}
	}

	for (int r = curRow - 1; r >= 0; r--) {
		Piece otherPiece = board.getPiece(r, curCol);
		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(r, curCol));
				break;
			}
		}
		else {
			validMoves.push_back(Point(r, curCol));
		}
	}

	for (int c = curCol + 1; c < 8; c++) {
		Piece otherPiece = board.getPiece(curRow, c);
		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(curRow, c));
				break;
			}
		}
		else {
			validMoves.push_back(Point(curRow, c));
		}
	}

	for (int c = curCol - 1; c >= 0; c--) {
		Piece otherPiece = board.getPiece(curRow, c);
		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(curRow, c));
				break;
			}
		}
		else {
			validMoves.push_back(Point(curRow, c));
		}
	}

	return validMoves;
}

vector<Point> Piece::knightMovesGen(Board board) {
	
	vector<Point> validMoves;

	int curRow = curLocation.row;
	int curCol = curLocation.col;

	validMoves.push_back(Point(curRow + 2, curCol + 1));
	validMoves.push_back(Point(curRow + 2, curCol - 1));
	validMoves.push_back(Point(curRow - 2, curCol - 1));
	validMoves.push_back(Point(curRow - 2, curCol + 1));
	validMoves.push_back(Point(curRow + 1, curCol - 2));
	validMoves.push_back(Point(curRow + 1, curCol + 2));
	validMoves.push_back(Point(curRow - 1, curCol - 2));
	validMoves.push_back(Point(curRow - 1, curCol + 2));

	for (int i = 0; i < validMoves.size(); i++) {
		if (!board.checkBounds(validMoves[i]))
			validMoves.erase(validMoves.begin() + i);
		else if (board.getPiece(validMoves[i].row, validMoves[i].col).returnColor() == color)
			validMoves.erase(validMoves.begin() + i);
	}

	return validMoves;
}

vector<Point> Piece::bishopMovesGen(Board board) {

	vector<Point> validMoves;

	int curRow = curLocation.row;
	int curCol = curLocation.col;
	int tempCol = curCol;

	//southeast
	for (int r = curRow + 1; r < 8; r++) {
		tempCol += 1;
		if (!board.checkBounds(Point(r, tempCol)))
			break;
		
		Piece otherPiece = board.getPiece(r, tempCol);

		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(r, tempCol));
				break;
			}
		}
		else {
			validMoves.push_back(Point(r, tempCol));
		}
	}
	
	tempCol = curCol;

	//southwest
	for (int r = curRow + 1; r < 8; r++) {
		tempCol -= 1;
		if (!board.checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board.getPiece(r, tempCol);

		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(r, tempCol));
				break;
			}
		}
		else {
			validMoves.push_back(Point(r, tempCol));
		}
	}

	tempCol = curCol;

	//northeast
	for (int r = curRow - 1; r >= 0; r--) {
		tempCol += 1;
		if (!board.checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board.getPiece(r, tempCol);

		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(r, tempCol));
				break;
			}
		}
		else {
			validMoves.push_back(Point(r, tempCol));
		}
	}

	tempCol = curCol;

	//northwest
	for (int r = curRow - 1; r >= 0; r--) {
		tempCol -= 1;
		if (!board.checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board.getPiece(r, tempCol);

		if (otherPiece.returnType() != Type::EMPTY) {
			if (otherPiece.returnColor() != color) {
				validMoves.push_back(Point(r, tempCol));
				break;
			}
		}
		else {
			validMoves.push_back(Point(r, tempCol));
		}
	}

	return validMoves;

}

vector<Point> Piece::kingMovesGen(Board board) {
	
	vector<Point> validMoves;

	int curRow = curLocation.row;
	int curCol = curLocation.col;

	validMoves.push_back(Point(curRow + 1, curCol));
	validMoves.push_back(Point(curRow - 1, curCol));
	validMoves.push_back(Point(curRow, curCol + 1));
	validMoves.push_back(Point(curRow, curCol - 1));
	validMoves.push_back(Point(curRow + 1, curCol + 1));
	validMoves.push_back(Point(curRow - 1, curCol + 2));
	validMoves.push_back(Point(curRow + 1, curCol - 2));
	validMoves.push_back(Point(curRow - 1, curCol - 2));


	for (int i = 0; i < validMoves.size(); i++) {
		if (!board.checkBounds(validMoves[i]))
			validMoves.erase(validMoves.begin() + i);
		else if (board.getPiece(validMoves[i].row, validMoves[i].col).returnColor() == color)
			validMoves.erase(validMoves.begin() + i);
	}

	return validMoves;
}

vector<Point> Piece::queenMovesGen(Board board) {
	vector<Point> validMovesBishop;
	vector<Point> validMovesQueen;

	validMovesBishop = bishopMovesGen(board);
	validMovesQueen = rookMovesGen(board);
	for (int i = 0; i < validMovesBishop.size(); i++) {
		validMovesQueen.push_back(validMovesBishop[i]);
	}

	return validMovesQueen;
}

vector<Point> Piece::pawnMovesGen(Board board) {

	vector<Point> validMoves;

	int curRow = curLocation.row;
	int curCol = curLocation.col;

	if (color == Color::BLACK) {

		if (board.checkBounds(Point(curRow + 1, curCol + 1))) {
			if (board.getPiece(curRow + 1, curCol + 1).returnColor() == Color::WHITE)
				validMoves.push_back(Point(curRow + 1, curCol + 1));
		}

		if (board.checkBounds(Point(curRow + 1, curCol - 1))) {
			if (board.getPiece(curRow + 1, curCol - 1).returnColor() == Color::WHITE)
				validMoves.push_back(Point(curRow + 1, curCol - 1));
		}

		if (board.checkBounds(Point(curRow + 1, curCol))) {
			if (board.getPiece(curRow + 1, curCol).returnType() == Type::EMPTY) {
				validMoves.push_back(Point(curRow + 1, curCol));

				if (board.checkBounds(Point(curRow + 2, curCol))) {
					if (status == Status::SPAWN && board.getPiece(curRow + 2, curCol).returnType() == Type::EMPTY) {
						validMoves.push_back(Point(curRow + 2, curCol));
						status = Status::INGAME;
					}
				}
			}
		}

	}
	else {

		if (board.checkBounds(Point(curRow - 1, curCol + 1))) {
			if (board.getPiece(curRow - 1, curCol + 1).returnColor() == Color::BLACK)
				validMoves.push_back(Point(curRow - 1, curCol + 1));
		}

		if (board.checkBounds(Point(curRow - 1, curCol - 1))) {
			if (board.getPiece(curRow - 1, curCol - 1).returnColor() == Color::BLACK)
				validMoves.push_back(Point(curRow - 1, curCol - 1));
		}

		if (board.checkBounds(Point(curRow - 1, curCol))) {
			if (board.getPiece(curRow - 1, curCol).returnType() == Type::EMPTY) {
				validMoves.push_back(Point(curRow - 1, curCol));

				if (board.checkBounds(Point(curRow - 2, curCol))) {
					if (status == Status::SPAWN && board.getPiece(curRow - 2, curCol).returnType() == Type::EMPTY) {
						validMoves.push_back(Point(curRow - 2, curCol));
						status = Status::INGAME;
					}
				}
			}
		}
	}

	return validMoves;
}


