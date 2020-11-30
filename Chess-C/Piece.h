#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Common.h"
#include "Board.h"

using namespace std;

class Piece {

public:

	/* Default constructor */
	Piece();
	/* Constructor with given values */
	Piece(Type piece, Color color);

	void setLocation(Point newLoc);
	Point getLocation();
	string returnBoardName();
	string returnName();
	Type returnType();
	Color returnColor();

private:
	Type piece;
	Color color;
	Status status;
	Point curLocation;

	Point startPoint;
	Point endPoint;

	// Check if movement from start to end point is valid
	bool rookMove(Point startPoint, Point endPoint, Board board);
	bool knightMove(Point startPoint, Point endPoint, Board board);
	bool bishopMove(Point startPoint, Point endPoint, Board board);
	bool kingMove(Point startPoint, Point endPoint, Board board);
	bool queenMove(Point startPoint, Point endPoint, Board board);
	bool pawnMove(Point startPoint, Point endPoint, Board board);

};
