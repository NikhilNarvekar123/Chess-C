#ifndef BOARDCLASS
#define BOARDCLASS

#include <string>
#include <vector>
#include <iostream>
#include "CommonData.h"

using namespace std;

class Board;

class Piece {

public:
	Piece();
	Piece(Type piece, Color color);
	Piece(int error);

	Point getLocation();
	string getBoardName();
	string getName();
	Type getType();
	Color getColor();
	Status getStatus();
	int getValue();
	bool isValid();

	void setLocation(Point newLoc);
	void setStatus(Status newStatus);

	vector<Point> generateMoves(Board board);

private:
	Type piece;
	Color color;
	Status status;
	Point curLocation;
	bool valid;

	vector<Point> rookMovesGen(Board board);
	vector<Point> knightMovesGen(Board board);
	vector<Point> bishopMovesGen(Board board);
	vector<Point> kingMovesGen(Board board);
	vector<Point> queenMovesGen(Board board);
	vector<Point> pawnMovesGen(Board board);

};

class Board {

public:
	Board();
	void initBoard();
	void printBoard(string boardType = "t");
	void printBoardFormat();
	void setBoard(vector<vector<Piece>> board);
	vector<vector<Piece>> returnBoard();
	bool checkBounds(Point p);

	Piece movePiece(Point startPt, Point endPt, Color playerColor);
	Piece getPiece(int row, int col);

	bool isInCheckWhite(Piece whiteKing, Board givenBoard);
	bool isInCheckBlack(Piece blackKing, Board givenBoard);
	bool isInCheckmateWhite(Piece whiteKing);
	bool isInCheckmateBlack(Piece blackKing);
	Color checkWin();
	Color printWinner();

private:
	// Matrix to hold board in
	vector<vector<Piece>> curBoard;

	// Labels to print out while board is being printed
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

};

#endif
