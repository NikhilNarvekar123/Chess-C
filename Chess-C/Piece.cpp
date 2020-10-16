#pragma once
#include "Piece.h";

Piece::Piece() {
	this->pieceToMove = PieceType::EMPTY;
	this->color = Color::NONE;
}

Piece::Piece(PieceType piece, Color color) {
	this->pieceToMove = piece;
	this->color = color;
	this->status = Status::SPAWN;
}

string Piece::returnBoardName() {
	string colorPostfix = "";
	if (this->color == Color::BLACK)
		colorPostfix = "b";
	else
		colorPostfix = "w";

	switch (pieceToMove) {
	case PieceType::ROOK:
		return "r" + colorPostfix;
	case PieceType::KNIGHT:
		return "h" + colorPostfix;
	case PieceType::BISHOP:
		return "b" + colorPostfix;
	case PieceType::KING:
		return "k" + colorPostfix;
	case PieceType::QUEEN:
		return "q" + colorPostfix;
	case PieceType::PAWN:
		return "p" + colorPostfix;
	default:
		return "  ";
	}
}

string Piece::returnName() {
	switch (pieceToMove) {
	case PieceType::ROOK:
		return "ROOK";
	case PieceType::KNIGHT:
		return "KNIGHT";
	case PieceType::BISHOP:
		return "BISHOP";
	case PieceType::KING:
		return "KING";
	case PieceType::QUEEN:
		return "QUEEN";
	case PieceType::PAWN:
		return "PAWN";
	default:
		return "EMPTY";
	}
}



Move Piece::movePiece(Point startPoint, Point endPoint, vector<vector<Piece>> curBoard) {
	Piece::startPoint = startPoint;
	Piece::endPoint = endPoint;
	this->boardCopy = curBoard;

	if (Piece::pieceToMove == PieceType::ROOK)
		return rookMove();
	else if (Piece::pieceToMove == PieceType::KNIGHT)
		return knightMove();
	else if (Piece::pieceToMove == PieceType::BISHOP)
		return bishopMove();
	else if (Piece::pieceToMove == PieceType::KING)
		return kingMove();
	else if (Piece::pieceToMove == PieceType::QUEEN)
		return rookMove();
	else if (Piece::pieceToMove == PieceType::PAWN)
		return rookMove();
	else {
		Move move;
		move.valid = false;
		return move;
	}
}

Move Piece::rookMove() {
	bool firstCheck = false;
	Move move;

	if (abs(startPoint.row - endPoint.row) == 0)
		firstCheck = true;
	else if(abs(startPoint.col - endPoint.col) == 0)
		firstCheck = true;
	
	if (!firstCheck) {
		move.valid = false;
		return move;
	} else {
		
		int rowDif = startPoint.row - endPoint.row;
		int colDif = startPoint.col - endPoint.col;

		//downward
		if (rowDif < 0) {
			for (int r = startPoint.row; r <= endPoint.row; r++) {
				Piece alongPiece = boardCopy[r][startPoint.col];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					move.valid = false;
					return move;
				}
			}
		}
		//upward
		if (rowDif > 0) {
			for (int r = startPoint.row; r >= endPoint.row; r--) {
				Piece alongPiece = boardCopy[r][startPoint.col];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					move.valid = false;
					return move;
				}
			}
		}
		//right
		if (colDif < 0) {
			for (int c = startPoint.col; c <= endPoint.col; c++) {
				Piece alongPiece = boardCopy[startPoint.row][c];
				if (alongPiece.returnName() != "EMPTY" && c != endPoint.col) {
					move.valid = false;
					return move;
				}
			}
		}
		//left
		if (colDif > 0) {
			for (int c = startPoint.col; c >= endPoint.col; c--) {
				Piece alongPiece = boardCopy[startPoint.row][c];
				if (alongPiece.returnName() != "EMPTY" && c != endPoint.col) {
					move.valid = false;
					return move;
				}
			}
		}

		move.valid = true;
		move.takenCol = endPoint.col;
		move.takenRow = endPoint.row;
		return move;
	}
}

Move Piece::knightMove() {

	bool firstCheck = false;
	Move move;
	if (abs(startPoint.row - endPoint.row) == 2 && abs(startPoint.col - endPoint.col) == 1)
		firstCheck = true;
	else if (abs(startPoint.row - endPoint.row) == 1 && abs(startPoint.col - endPoint.col) == 2)
		firstCheck = true;		

	if (!firstCheck) {
		move.valid = false;
		return move;
	}
	else {
		move.valid = true;
		move.takenCol = endPoint.col;
		move.takenRow = endPoint.row;
		return move;
	}
}

Move Piece::bishopMove() {

	bool firstCheck = false;
	Move move;

	if (abs(startPoint.row - endPoint.row) == abs(startPoint.col - endPoint.col))
		firstCheck = true;

	if (!firstCheck) {
		move.valid = false;
		return move;
	}
	else {

		int rowDif = startPoint.row - endPoint.row;
		int colDif = startPoint.col - endPoint.col;

		//southeast
		if (rowDif < 0 && colDif < 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r <= endPoint.row; r++) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					move.valid = false;
					return move;
				}
				c++;
			}
		}
		//southwest
		if (rowDif < 0 && colDif > 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r <= endPoint.row; r++) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					move.valid = false;
					return move;
				}
				c--;
			}
		}
		//northeast
		if (rowDif > 0 && colDif < 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r >= endPoint.row; r--) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					move.valid = false;
					return move;
				}
				c++;
			}
		}
		//northwest
		if (rowDif > 0 && colDif > 0) {
			int c = startPoint.col;
			for (int r = startPoint.row; r >= endPoint.row; r--) {
				Piece alongPiece = boardCopy[r][c];
				if (alongPiece.returnName() != "EMPTY" && r != endPoint.row) {
					move.valid = false;
					return move;
				}
				c--;
			}
		}


		move.valid = true;
		move.takenCol = endPoint.col;
		move.takenRow = endPoint.row;
		return move;
	}
}

Move Piece::kingMove() {

	bool firstCheck = false;
	Move move;

	if (abs(startPoint.row - endPoint.row) <= 1 && abs(startPoint.col - endPoint.col) <= 1)
		firstCheck = true;

	if (!firstCheck) {
		move.valid = false;
		return move;
	}
	else {
		move.valid = true;
		move.takenCol = endPoint.col;
		move.takenRow = endPoint.row;
		return move;
	}
}

Move Piece::queenMove() {

	Move move = bishopMove();
	if (move.valid == false)
		move = rookMove();
	
	return move;
}

Move Piece::pawnMove() {
	Move move;
	int rowDif = startPoint.row - endPoint.row;

	//if (startPoint.col != endPoint.col) {
	//	move.valid = false;
	//	return move;
	//}

	//
	//if (this->color == Color::BLACK) {

	//	if (!(rowDif < 0)) {
	//		move.valid = false;
	//		return move;
	//	}
	//}

	//if (this->color == Color::WHITE) {

	//	if (!(rowDif > 0)) {
	//		move.valid = false;
	//		return move;
	//	}
	//}


	//rowDif = abs(rowDif);

	//if (this->status == Status::SPAWN) {
	//	if (rowDif == 1 || rowDif == 2) {
	//		this->status = Status::INGAME;
	//	}
	//	else {
	//		move.valid = false;
	//		return move;
	//	}
	//}
	//else {
	//	if (rowDif != 1) {
	//		move.valid - false;
	//		return move;
	//	}
	//}
	
	move.valid = true;
	move.takenCol = endPoint.col;
	move.takenRow = endPoint.row;

	return move;

}