#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Common.h"
#include "Piece.h"

using namespace std;

class BoardManager {
public:
	// Default constructor
	Board();
	
	int movePieceAI(Point startPt, Point endpt);

	// Moves given piece from startposition to endposition
	int movePiece(string startPosition, string endPosition, int playerID);

	// Initalizes board
	void printBoard();

	// Draws board in console
	void refreshBoard();
	int checkWin();

	void setBoard(vector<vector<Piece>> newBoard);

	vector<vector<Piece>> returnBoard();

private:
	
	// Translates user input into actual board locations
	Point translateInput(string input);

	// Matrix to hold board in
	vector<vector<Piece>> curBoard;
	
	// Labels to print out while board is being printed
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

};