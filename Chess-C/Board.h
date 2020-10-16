#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Common.h"
#include "Piece.h"

using namespace std;

class Board {
public:
	Board();
	int movePiece(string startPosition, string endPosition);
	void refreshBoard();

private:

	PieceType findPieceType(string piece);
	Point translateInput(string input);

	vector<vector<Piece>> curBoard;
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };




};