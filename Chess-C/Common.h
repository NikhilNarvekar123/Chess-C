#pragma once

// Represents a point on the board (valid point used to indicate if point is within 8X8 grid)
struct Point {
	int row;
	int col;
	bool valid = true;
	int value;
	Point() {

	}
	Point(int r, int c) {
		row = r;
		col = c;
	}
};


struct Move {
	Point startPt;
	Point endPt;
	int value;
	Move() {};
	Move(Point start, Point end) {
		startPt = start;
		endPt = end;
	}
};