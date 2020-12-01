#include "Board_Piece.h"
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF

Board::Board() {
	initBoard();
}

vector<vector<Piece>> Board::returnBoard() {
	return curBoard;
}

void Board::setBoard(vector<vector<Piece>> board) {
	curBoard = board;
}

bool Board::checkBounds(Point p) {
	if (!(p.row >= 0 && p.row <= 7))
	return false;
	if (!(p.col >= 0 && p.col <= 7))
	return false;
}

void Board::initBoard() {
	Board::curBoard = { {Piece(Type::ROOK, Color::BLACK), Piece(Type::KNIGHT, Color::BLACK), Piece(Type::BISHOP, Color::BLACK),
		   Piece(Type::KING, Color::BLACK), Piece(Type::QUEEN, Color::BLACK), Piece(Type::BISHOP, Color::BLACK),
		   Piece(Type::KNIGHT, Color::BLACK), Piece(Type::ROOK, Color::BLACK)} ,
		  {Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK),
		   Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK),
		   Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK)} ,
		  {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
		  {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
		  {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
		  {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
		  {Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE),
		   Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE),
		   Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE)},
		  {Piece(Type::ROOK, Color::WHITE), Piece(Type::KNIGHT, Color::WHITE), Piece(Type::BISHOP, Color::WHITE),
		   Piece(Type::KING, Color::WHITE), Piece(Type::QUEEN, Color::WHITE), Piece(Type::BISHOP, Color::WHITE),
		   Piece(Type::KNIGHT, Color::WHITE), Piece(Type::ROOK, Color::WHITE)} };
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			curBoard[r][c].setLocation(Point(r, c));
		}
	}
}

void Board::printBoard() {
	cout << endl << endl;
	for (int i = 0; i < 8; i++) {
		printf("%6s", boardLabelsX[i].c_str());
	}
	cout << endl;
	for (int r = 0; r < 8; r++) {
		cout << boardLabelsY[r] << " ";
		for (int c = 0; c < 8; c++) {
			cout << "| " << curBoard[r][c].returnBoardName() << " |";
		}
		cout << endl << endl;
	}
	cout << endl;
}

Piece Board::movePiece(Point startPt, Point endPt, Color playerColor) {

	Piece startPiece = curBoard[startPt.row][startPt.col];
	Piece endPiece = curBoard[endPt.row][endPt.col];

	if (startPiece.returnType() == Type::EMPTY)
		return Piece(-1);
	if (startPiece.returnColor() == Color::WHITE && playerColor != Color::WHITE)
		return Piece(-1);
	if (startPiece.returnColor() == Color::BLACK && playerColor != Color::BLACK)
		return Piece(-1);
	if (startPt.row == endPt.row && startPt.col == endPt.col)
		return Piece(-1);

	vector<Point> validMoves = startPiece.generateMoves(*this);

	bool validMatch = false;
	for (Point validMove : validMoves) {
		if (endPt.row == validMove.row && endPt.col == validMove.col) {
			validMatch = true;
			break;
		}
	}
	
	// if user-endpt was in the valid moveset, make move
	if (validMatch) {
		curBoard[endPt.row][endPt.col] = startPiece;
		curBoard[startPt.row][startPt.col] = Piece();
	}
	else {
		// otherwise, return an invalid piece holder
		return Piece(-1);
	}

	// if user-endpt was occupied by enemy, then update taken piece
	if (endPiece.returnType() != Type::EMPTY) {
		endPiece.setLocation(Point(-1, -1));
		endPiece.setStatus(Status::TAKEN);
	}

	// return either taken or empty location
	return endPiece;
}

Piece Board::getPiece(int row, int col) {
	bool valid = checkBounds(Point(row, col));
	if (valid)
		return curBoard[row][col];
	return Piece(-1);
}

int Board::checkWin() {

	bool blackHasKing = false;
	bool whiteHasKing = false;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (curBoard[r][c].returnBoardName() == "kw")
				whiteHasKing = true;
			if (curBoard[r][c].returnBoardName() == "kb")
				blackHasKing = true;
		}
	}

	if (!blackHasKing) {
		return 1;
	}
	if (!whiteHasKing) {
		return 2;
	}

	// checkmate functionality
	return 0;
}
