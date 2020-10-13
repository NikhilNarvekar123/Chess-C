#pragma once
#include "Piece.h";


Piece::Piece(Pieces piece) {
	Piece::pieceToMove = piece;
}

string Piece::returnName() {
	switch (pieceToMove) {
	case Pieces::ROOK:
		return "ROOK";
	case Pieces::KNIGHT:
		return "KNIGHT";
	case Pieces::BISHOP:
		return "BISHOP";
	case Pieces::KING:
		return "KING";
	case Pieces::QUEEN:
		return "QUEEN";
	case Pieces::PAWN:
		return "PAWN";
	default:
		return "EMPTY";
	}
}

Pieces Piece::returnPiece() {
	return Piece::pieceToMove;
}

bool Piece::processMove(Point startPoint, Point endPoint) {
	Piece::startPoint = startPoint;
	Piece::endPoint = endPoint;

	if (Piece::pieceToMove == Pieces::ROOK)
		return rookMove();
	else if (Piece::pieceToMove == Pieces::KNIGHT)
		return knightMove();
	else if (Piece::pieceToMove == Pieces::BISHOP)
		return bishopMove();
	else if (Piece::pieceToMove == Pieces::KING)
		return kingMove();
	else if (Piece::pieceToMove == Pieces::QUEEN)
		return rookMove();
	else if (Piece::pieceToMove == Pieces::PAWN)
		return rookMove();
	else
		return false;

}

bool Piece::rookMove() {
	if (abs(startPoint.row - endPoint.row) == 0)
		return true;
	if(abs(startPoint.col - endPoint.col) == 0)
		return true;
	return false;
}

bool Piece::knightMove() {
	if (abs(startPoint.row - endPoint.row) == 2 && abs(startPoint.col - endPoint.col) == 1)
		return true;
	if (abs(startPoint.row - endPoint.row) == 1 && abs(startPoint.col - endPoint.col) == 2)
		return true;
	return false;
}

bool Piece::bishopMove() {
	if (abs(startPoint.row - endPoint.row) == abs(startPoint.col == endPoint.col))
		return true;
	return false;
}

bool Piece::kingMove() {
	if (abs(startPoint.row - endPoint.row) <= 1 && abs(startPoint.col - endPoint.col) <= 1)
		return true;
	return false;
}

bool Piece::queenMove() {
	bool validity = bishopMove();
	if (validity == false)
		validity = rookMove();
	return validity;
}

bool Piece::pawnMove() {
	return true; //error-checking more complicated
}