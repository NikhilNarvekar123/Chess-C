#include "Board.h"


Board::Board() {

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

void Board::refreshBoard() {
	cout << endl << endl;
	for (int i = 0; i < 8; i++) {
		printf("%6s", boardLabelsX[i].c_str());
	}
	cout << endl;
	for (int r = 0; r < 8; r++) {
		cout << boardLabelsY[r] << " ";
		for (int c = 0; c < 8; c++) {
			cout << "| " << curBoard[r][c].returnBoardName() << " |";
		}
		cout << endl << endl;
	}
	cout << endl;
}

int Board::movePiece(string startPosition, string endPosition) {
	
	Point startPoint = translateInput(startPosition);
	Point endPoint = translateInput(endPosition);
	

	if (startPoint.valid == false || endPoint.valid == false)
		return -1;
	if (startPoint.row == endPoint.row && startPoint.col == endPoint.col)
		return -1;
	
	Piece startPiece = curBoard[startPoint.row][startPoint.col];
	Piece endPiece = curBoard[endPoint.row][endPoint.col];

	Move move = startPiece.movePiece(startPoint, endPoint, curBoard);
	if (move.valid && endPiece.returnName() == "EMPTY") {
		curBoard[endPoint.row][endPoint.col] = startPiece;
		curBoard[startPoint.row][startPoint.col] = Piece();
		cout << startPiece.returnName() << " moved!" << endl;
		return 0;
	} else if (move.valid && endPiece.returnName() != "EMPTY") {
		curBoard[endPoint.row][endPoint.col] = startPiece;
		curBoard[startPoint.row][startPoint.col] = Piece();
		cout << startPiece.returnName() << " takes " << endPiece.returnName() << "!" << endl;
		return 1;
	}

	return -1;

}


Point Board::translateInput(string input) {
	
	int tempRow;
	int tempCol;
	

	for (int i = 0; i < 8; i++) {
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


PieceType Board::findPieceType(string piece) {
	//if (piece.find("r"))
	//	return Pieces::ROOK;
	//else if (piece.find("h"))
	//	return Pieces::KNIGHT;
	//else if (piece.find("b"))
	//	return Pieces::BISHOP;
	//else if (piece.find("k"))
	//	return Pieces::KING;
	//else if (piece.find("q"))
	//	return Pieces::QUEEN;
	//else if (piece.find("p"))
	//	return Pieces::PAWN;
	//else
	//	return Pieces::EMPTY;
	return PieceType::EMPTY;
}

