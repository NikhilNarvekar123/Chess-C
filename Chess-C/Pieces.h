#pragma once

enum class Pieces { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

struct Point {
	int row;
	int col;
	bool valid = true;
};