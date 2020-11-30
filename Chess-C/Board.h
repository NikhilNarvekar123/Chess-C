#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "CommonData.h"
#include "Piece.h"


class Board {

public:

	Board();
	bool checkBounds(Point p);
	void initBoard();
	void printBoard();

	int movePiece(string startPosition, string endPosition, Color playerColor);
	int checkWin();

private:

	// Matrix to hold board in
	vector<vector<Piece>> curBoard;

	// Labels to print out while board is being printed
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

};
