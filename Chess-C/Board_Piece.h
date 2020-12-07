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

	/* Default constructor */
	Piece();
	/* Constructor with given values */
	Piece(Type piece, Color color);
	Piece(int error);

	void setLocation(Point newLoc);
	Point getLocation();
	string returnBoardName();
	string returnName();
	Type returnType();
	Color returnColor();
	void setStatus(Status newStatus);
	Status getStatus();
	int returnValuation();
	bool isValid();

	vector<Point> generateMoves(Board board);

private:
	Type piece;
	Color color;
	Status status;
	Point curLocation;
	bool valid;

	Point startPoint;
	Point endPoint;

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
	bool checkBounds(Point p);
	void initBoard();
	void printBoard();

	Piece movePiece(Point startPt, Point endPt, Color playerColor);
	Piece getPiece(int row, int col);
	Color checkWin();
	bool isInCheckWhite(Piece whiteKing, Board givenBoard);
	bool isInCheckBlack(Piece blackKing, Board givenBoard);
	bool whiteInCheckmate(Piece whiteKing);
	bool blackInCheckmate(Piece blackKing);
	vector<vector<Piece>> returnBoard();

	void setBoard(vector<vector<Piece>> board);

private:

	// Matrix to hold board in
	vector<vector<Piece>> curBoard;

	// Labels to print out while board is being printed
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

	bool whiteInCheck;
	bool blackInCheck;


};




#endif
