#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Common.h"


using namespace std;

class Piece {

public:
	/* Default constructor */
	Piece();
	/* Constructor with given values */
	Piece(Type piece, Color color);

	/* Moves piece according to provided data */
	bool movePiece(Point startPoint, Point endPoint, vector<vector<Piece>> curBoard);
	
	/* Returns the display name of the piece */
	string returnBoardName();
	/* Returns the actual name of the piece */
	string returnName();
	Type returnType();
	Color returnColor();
	bool checkBounds(Point p);

private:
	// Instance variables to describe current piece
	Type piece;
	Color color;
	Status status;

	// Passed copy of board to modify
	vector<vector<Piece>> boardCopy;

	// Movement start and end points
	Point startPoint;
	Point endPoint;

	// Check if movement from start to end point is valid
	bool rookMove(Point startPoint, Point endPoint);
	bool knightMove(Point startPoint, Point endPoint);
	bool bishopMove(Point startPoint, Point endPoint);
	bool kingMove(Point startPoint, Point endPoint);
	bool queenMove(Point startPoint, Point endPoint);
	bool pawnMove(Point startPoint, Point endPoint);
	
};


