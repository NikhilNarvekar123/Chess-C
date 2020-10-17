#pragma once

// Represents a point on the board (valid point used to indicate if point is within 8X8 grid)
struct Point {
	int row;
	int col;
	bool valid = true;
};
