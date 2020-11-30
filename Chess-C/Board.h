#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "CommonData.h"
#include "Piece.h"


class Board {

public:

	Board();

	// Moves given piece from startposition to endposition
	int movePiece(string startPosition, string endPosition, int playerID);

	void initBoard();
	void printBoard();

	int checkWin();

	vector<vector<Piece>> returnBoard();

private:

	// Matrix to hold board in
	vector<vector<Piece>> curBoard;

	// Labels to print out while board is being printed
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

};







};
