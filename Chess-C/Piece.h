#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Common.h"

enum class PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };
enum class Color {BLACK, WHITE, NONE};
enum class Status {TAKEN, INGAME, SPAWN};

using namespace std;

class Piece {

public:
	Piece();
	Piece(PieceType piece, Color color);
	Move movePiece(Point startPoint, Point endPoint, vector<vector<Piece>> curBoard);
	string returnBoardName();
	string returnName();

private:
	PieceType pieceToMove;
	Color color;
	Status status;
	vector<vector<Piece>> boardCopy;

	Point startPoint;
	Point endPoint;

	Move rookMove();
	Move knightMove();
	Move bishopMove();
	Move kingMove();
	Move queenMove();
	Move pawnMove();
	
};


