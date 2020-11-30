#pragma once
#include "Board.h"
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF

// Initializes board to default state
Board::Board() {
	initBoard();
}

// Initializes board to default state
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
}

// Prints board to console
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


int Board::movePiece(Point startPt, Point endPt, Color playerColor) {

	Piece startPiece = curBoard[startPoint.row][startPoint.col];
	Piece endPiece = curBoard[endPoint.row][endPoint.col];

	if (startPiece.returnType() == Type::EMPTY)
		return -1;
	if (startPiece.returnColor() == Color::WHITE && playerColor != Color::WHITE)
		return -1;
	if (startPiece.returnColor() == Color::BLACK && playerColor != Color::BLACK)
		return -1;

	bool validMove = false;

	if (startPiece.returnType() == Type::ROOK)
		validMove = startPiece.rookMove(startPt, endPt);


	if (validMove && endPiece.returnType() == Type::EMPTY) {
		// If valid move to empty location, transfer board locations and output results
		curBoard[endPoint.row][endPoint.col] = startPiece;
		curBoard[startPoint.row][startPoint.col] = Piece();
		cout << startPiece.returnName() << " moved!" << endl;
		return 0;
	}
	else if (validMove && endPiece.returnType() != Type::EMPTY) {
		// If valid move to filled location, transfer board locations and output results
		curBoard[endPoint.row][endPoint.col] = startPiece;
		curBoard[startPoint.row][startPoint.col] = Piece();
		cout << startPiece.returnName() << " takes " << endPiece.returnName() << "!" << endl;
		return 1;
	}

	return -1;
}

// Translates user input from 'A1' to actual board position
Point Board::translateInput(string input) {

	int tempRow;
	int tempCol;

	// A-H is 0-7 position, 8-1 is 0-7 position
	for (int i = 0; i < 8; i++) {
		if (input.substr(0, 1) == boardLabelsX[i])
			tempCol = i;
		if (input.substr(1, 1) == boardLabelsY[i])
			tempRow = i;
	}

	Point p;
	p.row = tempRow;
	p.col = tempCol;

	// If end or start point out of grid, notify main method
	if (!(tempRow >= 0 && tempRow <= 7))
		p.valid = false;
	if (!(tempCol >= 0 && tempCol <= 7))
		p.valid = false;

	return p;
}

void Board::setBoard(vector<vector<Piece>> newBoard) {
	curBoard = newBoard;
}

int Board::movePieceAI(Point startPt, Point endpt) {

	Piece startPiece = curBoard[startPt.row][startPt.col];
	Piece endPiece = curBoard[endpt.row][endpt.col];

	if (endPiece.returnType() == Type::EMPTY) {
		// If valid move to empty location, transfer board locations and output results
		curBoard[endpt.row][endpt.col] = startPiece;
		curBoard[startPt.row][startPt.col] = Piece();
		cout << startPiece.returnName() << " moved!" << endl;
		return 0;
	}
	else if (endPiece.returnType() != Type::EMPTY) {
		// If valid move to filled location, transfer board locations and output results
		curBoard[endpt.row][endpt.col] = startPiece;
		curBoard[startPt.row][startPt.col] = Piece();
		cout << startPiece.returnName() << " takes " << endPiece.returnName() << "!" << endl;
		return 1;
	}

	return -1;
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
