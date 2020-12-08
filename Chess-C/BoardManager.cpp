#include "BoardManager.h"

// default constructor
BoardManager::BoardManager() {}

// makes sure player input is correct and passes move to board class to make
string BoardManager::makeMove(string userStartPt, string userEndPt, string playerColor, Board &board) {

	Color color = (playerColor == "black") ? Color::BLACK : Color::WHITE;

	Point startPt = translateInput(userStartPt);
	Point endPt = translateInput(userEndPt);
	
	Piece startPiece = board.getPiece(startPt.row, startPt.col);
	Piece endPiece = board.getPiece(endPt.row, endPt.col);
	Piece moveResult = board.movePiece(startPt, endPt, color);

	// depending on whether move was valid or not
	if (!moveResult.isValid())
		return "Invalid move! Turn skipped.";
	if (moveResult.getType() == Type::EMPTY)
		return startPiece.getName() + " moved!";
	if(moveResult.getType() != Type::EMPTY)
		return startPiece.getName() + " takes " + endPiece.getName() + "!";
}

// Translates user input from 'A1' to actual board position
Point BoardManager::translateInput(string input) {

	int tempRow;
	int tempCol;

	// A-H is 0-7 position, 8-1 is 0-7 position
	for (int i = 0; i < 8; i++) {
		if (input.substr(0, 1) == boardLabelsX[i] or input.substr(0,1) == boardLabelsX2[i])
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
	regex format("[A-H][1-8]");
	regex format2("[a-h][1-8]");
	if (regex_match(input, format) || regex_match(input, format2))
		isValid = true;
	else
		isValid = false;

	while (!isValid) {
		cout << "Incorrect input was entered. Make sure to follow the format \"A1\" " << endl;
		cin >> input;
		if (regex_match(input, format) || regex_match(input, format2))
			isValid = true;
		else
			isValid = false;

	}
}
