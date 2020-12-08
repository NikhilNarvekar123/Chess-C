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
// represents invalid piece
Piece::Piece(int error) {
	valid = false;
}


// returns location of piece
Point Piece::getLocation() {
	return curLocation;
}
// returns display name of piece ('rb')
string Piece::getBoardName() {
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
// returns actual name of piece ('rook')
string Piece::getName() {
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
// return piece type
Type Piece::getType() {
	return this->piece;
}
// returns piece color
Color Piece::getColor() {
	return this->color;
}
// returns piece status
Status Piece::getStatus() {
	return status;
}
// returns relative value of piece
int Piece::getValue() {
	switch(piece) {
		case Type::ROOK:
		return 5;
		break;
		case Type::KNIGHT:
		return 5;
		break;
		case Type::BISHOP:
		return 5;
		break;
		case Type::KING:
		return 100;
		break;
		case Type::QUEEN:
		return 50;
		break;
		case Type::PAWN:
		return 2;
		break;
		default:
		return 0;
		break;
	}
}
// returns whether piece is valid or not
bool Piece::isValid() {
	return valid;
}


// updates location of piece
void Piece::setLocation(Point newLoc) {
	curLocation = newLoc;
}
// updates status of piece
void Piece::setStatus(Status newStatus) {
	status = newStatus;
}


// generates all valid moves for given piece
vector<Point> Piece::generateMoves(Board board) {

	vector<Point> validMoves;

	switch (piece) {
	case Type::ROOK:
		validMoves = rookMovesGen(board);
		break;
	case Type::KNIGHT:
		validMoves = knightMovesGen(board);
		break;
	case Type::BISHOP:
		validMoves = bishopMovesGen(board);
		break;
	case Type::KING:
		validMoves = kingMovesGen(board);
		break;
	case Type::QUEEN:
		validMoves = queenMovesGen(board);
		break;
	case Type::PAWN:
		validMoves = pawnMovesGen(board);
		break;
	}

	return validMoves;
}

/* moves rook piece along horizontal and vertical axis until either
   a enemy or friendly piece is reached. Adds all possible moves to
	 vector.
*/
vector<Point> Piece::rookMovesGen(Board board) {

	vector<Point> validMoves;
	int curRow = curLocation.row;
	int curCol = curLocation.col;

	// downward moves
	for (int r = curRow + 1; r < 8; r++) {
		Piece otherPiece = board.getPiece(r, curCol);
		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(r, curCol));
			}
			break;
		}
		else {
			validMoves.push_back(Point(r, curCol));
		}
	}

	// upward moves
	for (int r = curRow - 1; r >= 0; r--) {
		Piece otherPiece = board.getPiece(r, curCol);
		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(r, curCol));
			}
			break;
		}
		else {
			validMoves.push_back(Point(r, curCol));
		}
	}

	// rightward moves
	for (int c = curCol + 1; c < 8; c++) {
		Piece otherPiece = board.getPiece(curRow, c);
		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(curRow, c));
			}
			break;
		}
		else {
			validMoves.push_back(Point(curRow, c));
		}
	}

	// leftward moves
	for (int c = curCol - 1; c >= 0; c--) {
		Piece otherPiece = board.getPiece(curRow, c);
		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(curRow, c));
			}
			break;
		}
		else {
			validMoves.push_back(Point(curRow, c));
		}
	}

	return validMoves;
}

/* moves knight piece to all possible relative locations. If each location
   is valid then add it to a vector.
*/
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

	for (int i = validMoves.size() - 1; i >= 0; i--) {
		if (!board.checkBounds(validMoves[i]))
			validMoves.erase(validMoves.begin() + i);
		else if (board.getPiece(validMoves[i].row, validMoves[i].col).getColor() == color)
			validMoves.erase(validMoves.begin() + i);
	}

	return validMoves;
}

/* moves bishop piece across all diagonals until either enemy or friendly piece
   is reached. Add all possible locations to vector.
*/
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

		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(r, tempCol));
			}
			break;
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

		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(r, tempCol));
			}
			break;
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

		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(r, tempCol));
			}
			break;
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

		if (otherPiece.getType() != Type::EMPTY) {
			if (otherPiece.getColor() != color) {
				validMoves.push_back(Point(r, tempCol));
			}
			break;
		}
		else {
			validMoves.push_back(Point(r, tempCol));
		}
	}

	return validMoves;
}

/* moves king piece to all possible relative locations. If each location
   is valid then add it to a vector.
*/
vector<Point> Piece::kingMovesGen(Board board) {

	vector<Point> validMoves;
	int curRow = curLocation.row;
	int curCol = curLocation.col;

	validMoves.push_back(Point(curRow + 1, curCol));
	validMoves.push_back(Point(curRow - 1, curCol));
	validMoves.push_back(Point(curRow, curCol + 1));
	validMoves.push_back(Point(curRow, curCol - 1));
	validMoves.push_back(Point(curRow + 1, curCol + 1));
	validMoves.push_back(Point(curRow - 1, curCol + 1));
	validMoves.push_back(Point(curRow + 1, curCol - 1));
	validMoves.push_back(Point(curRow - 1, curCol - 1));

	for (int i = validMoves.size() - 1; i >= 0; i--) {
		if (!board.checkBounds(validMoves[i]))
			validMoves.erase(validMoves.begin() + i);
		else if (board.getPiece(validMoves[i].row, validMoves[i].col).getColor() == color)
			validMoves.erase(validMoves.begin() + i);
	}

	return validMoves;
}

/* moves queen piece according to both rook and bishop methods (diagonals &
   horizontals/verticals). Adds all possible locations to vector.
*/
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

/* checks 1 (or 2) spaces ahead of pawn piece to see if valid location. Also
   checks surrounding spaces for possible captures. Adds all possible locations
	 to vector.
*/
vector<Point> Piece::pawnMovesGen(Board board) {

	vector<Point> validMoves;
	int curRow = curLocation.row;
	int curCol = curLocation.col;

	if (color == Color::BLACK) {

		// capturing southeastern piece
		if (board.checkBounds(Point(curRow + 1, curCol + 1))) {
			if (board.getPiece(curRow + 1, curCol + 1).getColor() == Color::WHITE)
				validMoves.push_back(Point(curRow + 1, curCol + 1));
		}

		// capturing southwestern piece
		if (board.checkBounds(Point(curRow + 1, curCol - 1))) {
			if (board.getPiece(curRow + 1, curCol - 1).getColor() == Color::WHITE)
				validMoves.push_back(Point(curRow + 1, curCol - 1));
		}

		// checking one & two spaces down
		if (board.checkBounds(Point(curRow + 1, curCol))) {
			if (board.getPiece(curRow + 1, curCol).getType() == Type::EMPTY) {
				validMoves.push_back(Point(curRow + 1, curCol));

				// only if pawn is in spawn
				if (board.checkBounds(Point(curRow + 2, curCol))) {
					if (status == Status::SPAWN && board.getPiece(curRow + 2, curCol).getType() == Type::EMPTY) {
						validMoves.push_back(Point(curRow + 2, curCol));
					}
				}
			}
		}

	}
	else {

		// capturing northeastern piece
		if (board.checkBounds(Point(curRow - 1, curCol + 1))) {
			if (board.getPiece(curRow - 1, curCol + 1).getColor() == Color::BLACK)
				validMoves.push_back(Point(curRow - 1, curCol + 1));
		}

		// capturing northwestern piece
		if (board.checkBounds(Point(curRow - 1, curCol - 1))) {
			if (board.getPiece(curRow - 1, curCol - 1).getColor() == Color::BLACK)
				validMoves.push_back(Point(curRow - 1, curCol - 1));
		}

		// checking one & two spaces ahead
		if (board.checkBounds(Point(curRow - 1, curCol))) {
			if (board.getPiece(curRow - 1, curCol).getType() == Type::EMPTY) {
				validMoves.push_back(Point(curRow - 1, curCol));

				// if pawn is in spawn, check two spaces ahead
				if (board.checkBounds(Point(curRow - 2, curCol))) {
					if (this->status == Status::SPAWN && board.getPiece(curRow - 2, curCol).getType() == Type::EMPTY) {
						validMoves.push_back(Point(curRow - 2, curCol));
					}
				}
			}
		}

	}

	return validMoves;
}
