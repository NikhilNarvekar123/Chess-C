#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Pieces.h"

using namespace std;

struct Point {
	int row;
	int col;
	bool valid = true;
};

class Board {
public:
	Board();
	int movePiece(string startPosition, string endPosition);


private:

	Pieces pieceToMove;
	Pieces pieceToTake;

	Pieces findPieceType(string piece);

	void refreshBoard();
	void initialize();
	Point translateInput(string input);

	vector<vector<string>> curBoard;
	const string boardLabelsY[8] = { "8", "7", "6", "5", "4", "3", "2", "1" };
	const string boardLabelsX[8] = { "A","B", "C", "D", "E", "F","G","H" };




};