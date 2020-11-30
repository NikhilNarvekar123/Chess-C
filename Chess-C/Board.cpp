#pragma once
#include "Board.h"
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF

Board::Board() {
	initBoard();
}

bool Piece::checkBounds(Point p) {
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


int Board::movePiece(Point startPt, Point endPt, Color playerColor) {

	Piece startPiece = curBoard[startPt.row][startPt.col];
	Piece endPiece = curBoard[endPt.row][endPt.col];

	if (startPiece.returnType() == Type::EMPTY)
		return -1;
	if (startPiece.returnColor() == Color::WHITE && playerColor != Color::WHITE)
		return -1;
	if (startPiece.returnColor() == Color::BLACK && playerColor != Color::BLACK)
		return -1;

	bool validMove = false;

	switch (startPiece) {
	case Type::ROOK:
		validMove = startPiece.rookMove(startPt, endPt, curBoard);
	case Type::KNIGHT:
		validMove = startPiece.knightMove(startPt, endPt, curBoard);
	case Type::BISHOP:
		validMove = startPiece.bishopMove(startPt, endPt, curBoard);
	case Type::KING:
		validMove = startPiece.kingMove(startPt, endPt, curBoard);
	case Type::QUEEN:
		validMove = startPiece.queenMove(startPt, endPt, curBoard);
	case Type::PAWN:
		validMove = startPiece.pawnMove(startPt, endPt, curBoard);
	default:
		return "EMPTY";
	}

	curBoard[endPt.row][endPt.col] = startPiece;
	curBoard[startPt.row][startPt.col] = Piece();

	if (validMove && endPiece.returnType() == Type::EMPTY)
		return 0;
	else if (validMove && endPiece.returnType() != Type::EMPTY)
		return 1;
	else
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
