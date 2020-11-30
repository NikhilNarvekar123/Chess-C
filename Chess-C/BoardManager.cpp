#pragma once
#include "BoardManager.h"


BoardManager::BoardManager() {
	player1Score = 0;
	player2Score = 0;
}

string BoardManager::makeMove(string userStartPt, string userEndPt, string playerColor, Board &board) {

	Color playerColor = (playerColor == "black") ? Color::BLACK : Color::WHITE;

	Point startPt = translateInput(userStartPt);
	Point endPt = translateInput(userEndPt);

	int moveResult = board.movePiece(startPt, endPt, playerColor);

	if (moveResult == 0)
		return startPiece.returnName() + " moved!";
	else if(moveResult == 1)
		return startPiece.returnName() + " takes " + endPiece.returnName() + "!";
	else
		return "Invalid Move!";
}

// Translates user input from 'A1' to actual board position
Point BoardManager::translateInput(string input) {

	int tempRow;
	int tempCol;

	// A-H is 0-7 position, 8-1 is 0-7 position
	for (int i = 0; i < 8; i++) {
		if (input.substr(0, 1) == boardLabelsX[i])
			tempCol = i;
		if (input.substr(1, 1) == boardLabelsY[i])
			tempRow = i;
	}

	Point p;
	p.row = tempRow;
	p.col = tempCol;

	return p;
}

// wrapper method for input-validifier which keeps prompting the user until valid input entered
void BoardManager::actionCheck(string& input) {

	bool isValid;
	regex format("[A-Z][1-8]");
	regex format2("[a-z][1-8]");
	if (regex_match(input, format) || regex_match(input, format2))
		isValid = true;
	else
		isValid = false;

	while (!isValid) {
		cout << "Incorrect input was entered. Make sure to follow the format \"A1\" " << endl;
		cin >> input;
		isValid = inputValidifier(input);
	}
}
