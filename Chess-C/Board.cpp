#include "Board.h"


Board::Board() {
	Board::curBoard = { {"rb","hb","bb","kb","qb","bb","hb","rb"},
						{"pb","pb","pb","pb","pb","pb","pb","pb"},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"pw","pw","pw","pw","pw","pw","pw","pw"},
						{"rw","hw","bw","kw","qw","bw","hw","rw"} };

}

void Board::initialize() {
	cout << "";
	for (int i = 0; i < 8; i++) {
		printf("%6s", boardLabelsX[i].c_str());
	}
	cout << endl;
	for (int r = 0; r < 8; r++) {
		cout << boardLabelsY[r] << " ";
		for (int c = 0; c < 8; c++) {
			cout << "| " << curBoard[r][c] << " |";
		}
		cout << endl << endl;
	}
}

int Board::movePiece(string startPosition, string endPosition) {
	
	Point startPoint = translateInput(startPosition);
	Point endPoint = translateInput(endPosition);

	if (startPoint.valid == false || endPoint.valid == false)
		return -1;

	string startPiece = Board::curBoard[startPoint.row][startPoint.col];
	Piece pieceToMove(findPieceType(startPiece));
	string endPiece = Board::curBoard[endPoint.row][endPoint.col];
	Piece pieceToTake(findPieceType(endPiece));

	bool validMove = pieceToMove.processMove(startPoint, endPoint);
	if (!validMove) {
		return -1;
	}
	else if (pieceToTake.returnPiece() == Pieces::EMPTY) {
		Board::curBoard[endPoint.row][endPoint.col] = startPiece;
		Board::curBoard[startPoint.row][endPoint.col] = "  ";
		cout << pieceToMove.returnName() << "moved" << endl;
		return 0;
	}
	else if (pieceToTake.returnPiece() != Pieces::EMPTY) {
		Board::curBoard[endPoint.row][endPoint.col] = startPiece;
		Board::curBoard[startPoint.row][endPoint.col] = "  ";
		cout << pieceToMove.returnName() << " moved\n" << endl;
		cout << pieceToTake.returnName() << " was taken!\n" << endl;
		return 1;
	}

	return -1;

}


Point Board::translateInput(string input) {
	
	int tempRow;
	int tempCol;
	

	for (int i = 0; i < 8; i++) {
		cout << i << input.substr(0,1);
		if (input.substr(0, 1) == boardLabelsX[i])
			tempCol = i;
		if (input.substr(1, 1) == boardLabelsY[i])
			tempRow = i;
		
	}
	
	Point p;
	p.row = tempRow;
	p.col = tempCol;
	
	if (!(tempRow >= 0 && tempRow <= 7))
		p.valid = false;
	if (!(tempCol >= 0 && tempRow <= 7))
		p.valid = false;

	return p;
}


Pieces Board::findPieceType(string piece) {
	if (piece.find("r"))
		return Pieces::ROOK;
	else if (piece.find("h"))
		return Pieces::KNIGHT;
	else if (piece.find("b"))
		return Pieces::BISHOP;
	else if (piece.find("k"))
		return Pieces::KING;
	else if (piece.find("q"))
		return Pieces::QUEEN;
	else if (piece.find("p"))
		return Pieces::PAWN;
	else
		return Pieces::EMPTY;
}


void Board::refreshBoard() {
	initialize();
}


