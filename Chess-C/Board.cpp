#pragma once
#include "Board.h"

// Default constructor
Board::Board() {
	// Initialize board to be a matrix of piece objects
	Board::initializeBoard();
}

void Board::initializeBoard() {
	Board::curBoard = { {Piece(PieceType::ROOK, Color::BLACK), Piece(PieceType::KNIGHT, Color::BLACK), Piece(PieceType::BISHOP, Color::BLACK),
						 Piece(PieceType::KING, Color::BLACK), Piece(PieceType::QUEEN, Color::BLACK), Piece(PieceType::BISHOP, Color::BLACK),
						 Piece(PieceType::KNIGHT, Color::BLACK), Piece(PieceType::ROOK, Color::BLACK)} ,
						{Piece(PieceType::PAWN, Color::BLACK), Piece(PieceType::PAWN, Color::BLACK), Piece(PieceType::PAWN, Color::BLACK),
						 Piece(PieceType::PAWN, Color::BLACK), Piece(PieceType::PAWN, Color::BLACK), Piece(PieceType::PAWN, Color::BLACK),
						 Piece(PieceType::PAWN, Color::BLACK), Piece(PieceType::PAWN, Color::BLACK)} ,
						{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
						{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
						{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
						{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
						{Piece(PieceType::PAWN, Color::WHITE), Piece(PieceType::PAWN, Color::WHITE), Piece(PieceType::PAWN, Color::WHITE),
						 Piece(PieceType::PAWN, Color::WHITE), Piece(PieceType::PAWN, Color::WHITE), Piece(PieceType::PAWN, Color::WHITE),
						 Piece(PieceType::PAWN, Color::WHITE), Piece(PieceType::PAWN, Color::WHITE)},
						{Piece(PieceType::ROOK, Color::WHITE), Piece(PieceType::KNIGHT, Color::WHITE), Piece(PieceType::BISHOP, Color::WHITE),
						 Piece(PieceType::KING, Color::WHITE), Piece(PieceType::QUEEN, Color::WHITE), Piece(PieceType::BISHOP, Color::WHITE),
						 Piece(PieceType::KNIGHT, Color::WHITE), Piece(PieceType::ROOK, Color::WHITE)} };
}

vector<vector<Piece>> Board::returnBoard() {
	return this->curBoard;
}

// Prints board to console (can improve formatting or even add better graphics)
void Board::refreshBoard() {
	cout << endl << endl;
	for (int i = 0; i < 8; i++) {
		printf("%6s", boardLabelsX[i].c_str());
	}
	cout << endl;
	for (int r = 0; r < 8; r++) {
		cout << boardLabelsY[r] << " ";
		for (int c = 0; c < 8; c++) {
			Point p;
			p.col = c;
			p.row = r;
			curBoard[r][c].updateLocation(p);
			cout << "| " << curBoard[r][c].returnBoardName() << " |";
		}
		cout << endl << endl;
	}
	cout << endl;

}

int Board::movePieceAI(Point startPt, Point endpt, int playerID) {
	
	Piece startPiece = curBoard[startPt.row][startPt.col];
	Piece endPiece = curBoard[endpt.row][endpt.col];

	if (endPiece.returnName() == "EMPTY") {

		// If valid move to empty location, transfer board locations and output results 
		curBoard[endpt.row][endpt.col] = startPiece;
		curBoard[startPt.row][startPt.col] = Piece();
		cout << startPiece.returnName() << " moved!" << endl;
		return 0;
	}
	else if (endPiece.returnName() != "EMPTY") {

		// If valid move to filled location, transfer board locations and output results
		curBoard[endpt.row][endpt.col] = startPiece;
		curBoard[startPt.row][startPt.col] = Piece();
		cout << startPiece.returnName() << " takes " << endPiece.returnName() << "!" << endl;
		return 1;
	}

	return -1;
}


// Moves piece given start and end position (only if valid)
int Board::movePiece(string startPosition, string endPosition, int playerID) {
	
	// Get index position of both start and end points in the board
	Point startPoint = translateInput(startPosition);
	Point endPoint = translateInput(endPosition);

	// If not valid positions, raise an error (-1)
	if (startPoint.valid == false || endPoint.valid == false)
		return -1;

	// If start and end positions are the same, raise an error (-1)
	if (startPoint.row == endPoint.row && startPoint.col == endPoint.col)
		return -1;
	
	// With valid positions, get pieces at start and end positions
	Piece startPiece = curBoard[startPoint.row][startPoint.col];
	Piece endPiece = curBoard[endPoint.row][endPoint.col];

	// Simulate moving piece and check if valid move given board state
	bool validMove = startPiece.movePiece(startPoint, endPoint, curBoard, playerID);

	if (validMove && endPiece.returnName() == "EMPTY") {
		
		// If valid move to empty location, transfer board locations and output results 
		curBoard[endPoint.row][endPoint.col] = startPiece;
		curBoard[startPoint.row][startPoint.col] = Piece();
		cout << startPiece.returnName() << " moved!" << endl;
		return 0;
	} 
	else if (validMove && endPiece.returnName() != "EMPTY") {
		
		// If valid move to filled location, transfer board locations and output results
		curBoard[endPoint.row][endPoint.col] = startPiece;
		curBoard[startPoint.row][startPoint.col] = Piece();
		cout << startPiece.returnName() << " takes " << endPiece.returnName() << "!" << endl;
		return 1;
	}

	return -1;
}

// Translates user input from 'A1' to actual board position
Point Board::translateInput(string input) {
	
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
	
	// If end or start point out of grid, notify main method
	if (!(tempRow >= 0 && tempRow <= 7))
		p.valid = false;
	if (!(tempCol >= 0 && tempCol <= 7))
		p.valid = false;

	return p;
}
