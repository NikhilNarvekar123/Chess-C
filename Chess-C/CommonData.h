#pragma once

/* common data across the AI, Board Manager, and Board classes */

// Represents a point on the board
struct Point {
	int row;
	int col;
	Point() {}
	Point(int r, int c) : row{ r }, col{ c } {}
};

// Represents different types of game-pieces
enum class Type { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

// Represent different colors of board
enum class Color { BLACK, WHITE, EMPTY, CHECK_BLACK, CHECK_WHITE };

// Represent different states of a piece (primarily used for pawns)
enum class Status { TAKEN, INGAME, SPAWN, EMPTY };
