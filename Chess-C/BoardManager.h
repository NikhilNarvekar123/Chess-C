#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Common.h"
#include "Piece.h"
#include "Board.h"

using namespace std;

class BoardManager {
public:

	// Default constructor
	BoardManager();

	Point translateInput(string input);
	void makeMove(Point startPt, Point endPt, Color playerColor);
	void actionCheck(string& input);
	void displayScore();


private
	int player1Score;
	int player2Score;

};
