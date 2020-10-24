#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Common.h"

// Represents different types of game-pieces
enum class PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

// Represent different colors of board
enum class Color {BLACK, WHITE, EMPTY};

// Represent different states of a piece (primarily used for pawns)
enum class Status {TAKEN, INGAME, SPAWN, EMPTY};

using namespace std;

class Piece {

public:
	/* Default constructor */
	Piece();
	/* Constructor with given values */
	Piece(PieceType piece, Color color);

	/* Moves piece according to provided data */
	bool movePiece(Point startPoint, Point endPoint, vector<vector<Piece>> curBoard, int playerID);
	
	/* Returns the display name of the piece */
	string returnBoardName();
	/* Returns the actual name of the piece */
	string returnName();

private:
	// Instance variables to describe current piece
	PieceType piece;
	Color color;
	Status status;

	// Passed copy of board to modify
	vector<vector<Piece>> boardCopy;
	int playerID = 0;

	// Movement start and end points
	Point startPoint;
	Point endPoint;

	// Check if movement from start to end point is valid
	bool rookMove();
	bool knightMove();
	bool bishopMove();
	bool kingMove();
	bool queenMove();
	bool pawnMove();
	
};


