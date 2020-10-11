#pragma once
#include "Piece.h";

using namespace std;

Piece::Piece(Pieces piece) {
	Piece::pieceToMove = piece;
}

bool Piece::processMove(Point startPoint, Point endPoint) {
	Piece::startPoint = startPoint;
	Piece::endPoint = endPoint;

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