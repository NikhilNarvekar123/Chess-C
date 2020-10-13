#pragma once
#include "Pieces.h";
#include <iostream>
#include <string>


using namespace std;

class Piece {

public:
	Piece(Pieces piece);
	bool processMove(Point startPoint, Point endPoint);
	string returnName();
	Pieces returnPiece();

private:
	Pieces pieceToMove;
	Point startPoint;
	Point endPoint;

	bool rookMove();
	bool knightMove();
	bool bishopMove();
	bool kingMove();
	bool queenMove();
	bool pawnMove();
	
};


