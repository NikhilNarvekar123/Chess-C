#pragma once

struct Point {
	int row;
	int col;
	bool valid = true;
};

struct Move {
	bool valid = true;
	int takenRow = -1;
	int takenCol = -1;
};