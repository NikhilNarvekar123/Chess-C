#pragma once
#include "Pieces.h";
#include <iostream>

struct Point {
	int row;
	int col;
	bool valid = true;
};

class Piece {

public:
	Piece(Pieces piece);
	bool processMove(Point startPoint, Point endPoint);


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


